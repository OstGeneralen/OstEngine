// Kasper "OstGeneralen" Esbjornsson - 2026
#include "MaterialCompiler.h"

#include "MaterialCompilerIncludeHandler.h"
#include "RHI/RHIInternal.h"
#include "Rendering/RenderPipelineConstants.h"

#include <OstLog.h>

#include <Math/Math.h>
#include <Memory/Memory.h>
#include <Utility/File.h>

using namespace ost;

// ------------------------------------------------------------

auto MaterialCompileLog = Log::NewCategory("MaterialCompiler");

const std::filesystem::path MaterialShaderRootPath = "Engine/Shader/Material";

// ------------------------------------------------------------

EMaterialPropertyType ExtractPropertyType(ID3D11ShaderReflectionType* pDxType)
{
    D3D11_SHADER_TYPE_DESC dxTypeDesc = {};
    pDxType->GetDesc(&dxTypeDesc);

    const UINT rows = dxTypeDesc.Rows;
    const UINT columns = dxTypeDesc.Columns;

    if (rows != 1)
    {
        // Unsupported
        return EMaterialPropertyType::Unknown;
    }

    // clang-format off
    if (columns == 1)
    {
        switch(dxTypeDesc.Type)
        {
            case D3D_SVT_FLOAT: return EMaterialPropertyType::Float;
            case D3D_SVT_UINT: return EMaterialPropertyType::Uint;
        }
    }
    else if(columns == 2)
    {
        switch(dxTypeDesc.Type)
        {
            case D3D_SVT_FLOAT: return EMaterialPropertyType::Float2;
            case D3D_SVT_UINT: return EMaterialPropertyType::Uint2;
        }
    }
    else if(columns == 3)
    {
        switch(dxTypeDesc.Type)
        {
            case D3D_SVT_FLOAT: return EMaterialPropertyType::Float3;
            case D3D_SVT_UINT: return EMaterialPropertyType::Uint3;
        }
    }
    else if(columns == 4)
    {
        switch(dxTypeDesc.Type)
        {
            case D3D_SVT_FLOAT: return EMaterialPropertyType::Float4;
            case D3D_SVT_UINT: return EMaterialPropertyType::Uint4;
        }
    }
    // clang-format on

    return EMaterialPropertyType::Unknown;
}

// ------------------------------------------------------------

namespace MaterialVertexLayout
{
    template <EMaterialDomain TDomain>
    List<VertexElement> GetVertexLayout()
    {
        return {};
    }

    template <>
    List<VertexElement> GetVertexLayout<EMaterialDomain::SurfaceLit>()
    {
        return {{"POSITION", EDataSize::Float4},  // Position
                {"NORMAL", EDataSize::Float3},    // Normal
                {"TANGENT", EDataSize::Float3},   // Tangent
                {"COLOR", EDataSize::Float4},     // Color
                {"TEXCOORD", EDataSize::Float2}}; // UV
    }

} // namespace MaterialVertexLayout

// ------------------------------------------------------------

MaterialCompiler::MaterialCompiler(const MaterialDesc& desc)
{
    _materialShaderPath = desc.materialShaderPath;

    switch (desc.domain)
    {
    case EMaterialDomain::SurfaceLit: {

        _domainShaderPath = MaterialShaderRootPath / "MaterialShader_LitSurface.hlsl";
        _psoDesc.vertexLayout = MaterialVertexLayout::GetVertexLayout<EMaterialDomain::SurfaceLit>();
        _psoDesc.primitiveTopology = EPrimitiveTopology::TriangleList;
        break;
    }
    default:
        _domainShaderPath = "";
        break;
    }
}

// ------------------------------------------------------------

const PipelineStateObjectDesc& ost::MaterialCompiler::GetCompiledPSODesc() const
{
    return _psoDesc;
}

const MaterialPropertiesDesc& ost::MaterialCompiler::GetCompiledPropertySet() const
{
    return _materialProperties;
}

const List<MaterialTextureDesc> ost::MaterialCompiler::GetCompiledTextureDescs() const
{
    List<MaterialTextureDesc> list;
    for (const auto& [slotType, desc] : _textureDescs)
    {
        list.Add(desc);
    }
    return list;
}

// ------------------------------------------------------------

bool ost::MaterialCompiler::Compile()
{
    if (_domainShaderPath.empty())
    {
        Log::Error(MaterialCompileLog, "Material '{}' failure. Invalid domain type.", _materialShaderPath.string());
        return false;
    }

    // 1. Compile the shaders
    MaterialCompilerIncludeHandler includeHandler(MaterialShaderRootPath, _materialShaderPath);

    Blob shaderSourceCode = FileUtility::ReadFileToBlob(_domainShaderPath.string());

    ComPtr<ID3DBlob> errorBlob;

    HRESULT compileResult = S_OK;

    { // Compile Vertex Shader
        compileResult =
            D3DCompile(shaderSourceCode.Data(), shaderSourceCode.Size(), NULL, NULL, &includeHandler, "VSMain", "vs_4_1", D3DCOMPILE_DEBUG, 0, &_vsBytecode, &errorBlob);

        if (FAILED(compileResult))
        {
            std::string errorMsg = static_cast<const char*>(errorBlob->GetBufferPointer());
            Log::Error(MaterialCompileLog, "Material '{}' compile failure: '{}'", _materialShaderPath.string(), errorMsg);
            return false;
        }

        _psoDesc.vertexShader.bytecodeSize = _vsBytecode->GetBufferSize();
        _psoDesc.vertexShader.pBytecode = _vsBytecode->GetBufferPointer();
    }

    { // Compile Pixel Shader
        compileResult =
            D3DCompile(shaderSourceCode.Data(), shaderSourceCode.Size(), NULL, NULL, &includeHandler, "PSMain", "ps_4_1", D3DCOMPILE_DEBUG, 0, &_psBytecode, &errorBlob);

        if (FAILED(compileResult))
        {
            std::string errorMsg = static_cast<const char*>(errorBlob->GetBufferPointer());
            Log::Error(MaterialCompileLog, "Material '{}' compile failure: '{}'", errorMsg);
            return false;
        }

        _psoDesc.pixelShader.bytecodeSize = _psBytecode->GetBufferSize();
        _psoDesc.pixelShader.pBytecode = _psBytecode->GetBufferPointer();
    }

    // 2. Reflect both shaders to populate the set of properties
    ExtractProperties(_vsBytecode);
    ExtractProperties(_psBytecode);

    // 3. We're done. The user can now call the getters to extract the valid data :)
    return true;
}

// ------------------------------------------------------------

void ost::MaterialCompiler::ExtractProperties(const ComPtr<ID3DBlob>& from)
{
    ComPtr<ID3D11ShaderReflection> reflection;
    D3DReflect(from->GetBufferPointer(), from->GetBufferSize(), IID_ID3D11ShaderReflection, &reflection);

    D3D11_SHADER_DESC desc = {};
    reflection->GetDesc(&desc);

    std::string propertiesBufferName = "";

    for (UINT bindingIndex = 0; bindingIndex < desc.BoundResources; ++bindingIndex)
    {
        D3D11_SHADER_INPUT_BIND_DESC bindDesc = {};
        reflection->GetResourceBindingDesc(bindingIndex, &bindDesc);
        if (bindDesc.Type == D3D_SIT_CBUFFER && bindDesc.BindPoint == PipelineConstant::Get(EBufferSlot::MaterialProperties))
        {
            propertiesBufferName = bindDesc.Name;
            continue;
        }
        else if (bindDesc.Type == D3D_SIT_TEXTURE)
        {
            MaterialTextureDesc texDesc = {};
            texDesc.name = bindDesc.Name;
            texDesc.textureType = static_cast<EMaterialTexture>(bindDesc.BindPoint);
            _textureDescs.InsertOrOverwrite(texDesc.textureType, texDesc);
        }
    }

    if (propertiesBufferName.empty())
    {
        // No properties buffer could be found
        return;
    }

    auto propertiesBuffer = reflection->GetConstantBufferByName(propertiesBufferName.c_str());
    D3D11_SHADER_BUFFER_DESC bufferDesc = {};
    propertiesBuffer->GetDesc(&bufferDesc);
    _materialProperties.totalSize = math::Max<SizeType>(_materialProperties.totalSize, static_cast<SizeType>(bufferDesc.Size));

    for (UINT bufferVariableIndex = 0; bufferVariableIndex < bufferDesc.Variables; ++bufferVariableIndex)
    {
        auto property = propertiesBuffer->GetVariableByIndex(bufferVariableIndex);
        D3D11_SHADER_VARIABLE_DESC propertyDesc = {};
        property->GetDesc(&propertyDesc);

        MaterialProperty materialProperty;
        materialProperty.dataByteOffset = static_cast<SizeType>(propertyDesc.StartOffset);
        materialProperty.name = propertyDesc.Name;
        materialProperty.type = ExtractPropertyType(property->GetType());

        _materialProperties.propertyMap.InsertOrOverwrite(materialProperty.name, materialProperty);
    }
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------