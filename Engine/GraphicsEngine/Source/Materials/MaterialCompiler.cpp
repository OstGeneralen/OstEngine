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

    template <>
    List<VertexElement> GetVertexLayout<EMaterialDomain::Fullscreen>()
    {
        return {{"POSITION", EDataSize::Float4},  // Position
                {"TEXCOORD", EDataSize::Float2}}; // UV
    }

} // namespace MaterialVertexLayout

// ------------------------------------------------------------

MaterialCompiler::MaterialCompiler(const MaterialDesc& desc)
{
    _materialShaderPath = desc.materialShaderPath;

    _blendState = desc.blending;

    switch (desc.domain)
    {
    case EMaterialDomain::SurfaceLit: {
        _domainVertexMain = "VSMain_Surface";
        _domainPixelMainFwd = "PSMain_LitSurface_Forward";
        _domainPixelMainGeometry = "PSMain_Surface_Geometry";
        _psoDescForward.vertexLayout = MaterialVertexLayout::GetVertexLayout<EMaterialDomain::SurfaceLit>();
        _psoDescForward.primitiveTopology = EPrimitiveTopology::TriangleList;
        _psoDescDeferred.vertexLayout = MaterialVertexLayout::GetVertexLayout<EMaterialDomain::SurfaceLit>();
        _psoDescDeferred.primitiveTopology = EPrimitiveTopology::TriangleList;
        break;
    }
    case EMaterialDomain::Fullscreen: {
        _domainVertexMain = "VSMain_Fullscreen";
        _domainPixelMainFwd = "PSMain_Surface_Lit";
        _domainPixelMainGeometry = "PSMain_Surface_Lit";
        _psoDescForward.vertexLayout = MaterialVertexLayout::GetVertexLayout<EMaterialDomain::Fullscreen>();
        _psoDescForward.primitiveTopology = EPrimitiveTopology::TriangleList;
        _psoDescDeferred.vertexLayout = MaterialVertexLayout::GetVertexLayout<EMaterialDomain::Fullscreen>();
        _psoDescDeferred.primitiveTopology = EPrimitiveTopology::TriangleList;
        break;
    }
    default:
        break;
    }
}

// ------------------------------------------------------------

const PipelineStateObjectDesc& ost::MaterialCompiler::GetCompiledPSODescForward() const
{
    return _psoDescForward;
}

const PipelineStateObjectDesc& ost::MaterialCompiler::GetCompiledPSODescDeferred() const
{
    return _psoDescDeferred;
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
    constexpr std::string_view vsPath = "Engine/Shader/VertexShaders.hlsl";
    constexpr std::string_view psPath = "Engine/Shader/PixelShaders.hlsl";

    _psoDescDeferred.blendState = _blendState;
    _psoDescForward.blendState = _blendState;

    // 1. Compile the shaders
    MaterialCompilerIncludeHandler vertexIncludeHandler(vsPath, _materialShaderPath);
    MaterialCompilerIncludeHandler pixelIncludeHandler(psPath, _materialShaderPath);

    Blob vertexShaderSourceCode = FileUtility::ReadFileToBlob(std::string(vsPath));
    Blob pixelShaderSourceCode = FileUtility::ReadFileToBlob(std::string(psPath));

    ComPtr<ID3DBlob> errorBlob;

    HRESULT compileResult = S_OK;

    const std::string materialPath = _materialShaderPath.string();

    { // Compile Vertex Shader
        compileResult = D3DCompile(vertexShaderSourceCode.Data(), vertexShaderSourceCode.Size(), NULL, NULL, &vertexIncludeHandler, _domainVertexMain.c_str(), "vs_4_1",
                                   D3DCOMPILE_DEBUG, 0, &_vsBytecode, &errorBlob);

        if (FAILED(compileResult))
        {
            std::string errorMsg = static_cast<const char*>(errorBlob->GetBufferPointer());
            Log::Error(MaterialCompileLog, "Material '{}' compile failure: '{}'", materialPath, errorMsg);
            return false;
        }

        _psoDescForward.vertexShader.bytecodeSize = _vsBytecode->GetBufferSize();
        _psoDescForward.vertexShader.pBytecode = _vsBytecode->GetBufferPointer();
        _psoDescDeferred.vertexShader.bytecodeSize = _vsBytecode->GetBufferSize();
        _psoDescDeferred.vertexShader.pBytecode = _vsBytecode->GetBufferPointer();
    }

    { // Compile Pixel Shader for Forward Rendering
        compileResult = D3DCompile(pixelShaderSourceCode.Data(), pixelShaderSourceCode.Size(), NULL, NULL, &pixelIncludeHandler, _domainPixelMainFwd.c_str(), "ps_4_1",
                                   D3DCOMPILE_DEBUG, 0, &_psBytecodeFwd, &errorBlob);

        if (FAILED(compileResult))
        {
            std::string errorMsg = static_cast<const char*>(errorBlob->GetBufferPointer());
            Log::Error(MaterialCompileLog, "Material '{}' compile failure: '{}'", materialPath, errorMsg);
            return false;
        }

        _psoDescForward.pixelShader.bytecodeSize = _psBytecodeFwd->GetBufferSize();
        _psoDescForward.pixelShader.pBytecode = _psBytecodeFwd->GetBufferPointer();
    }

    { // Compile Pixel Shader for Deferred Rendering
        compileResult = D3DCompile(pixelShaderSourceCode.Data(), pixelShaderSourceCode.Size(), NULL, NULL, &pixelIncludeHandler, _domainPixelMainGeometry.c_str(),
                                   "ps_4_1", D3DCOMPILE_DEBUG, 0, &_psBytecodeDef, &errorBlob);

        if (FAILED(compileResult))
        {
            std::string errorMsg = static_cast<const char*>(errorBlob->GetBufferPointer());
            Log::Error(MaterialCompileLog, "Material '{}' compile failure: '{}'", materialPath, errorMsg);
            return false;
        }

        _psoDescDeferred.pixelShader.bytecodeSize = _psBytecodeDef->GetBufferSize();
        _psoDescDeferred.pixelShader.pBytecode = _psBytecodeDef->GetBufferPointer();
    }

    // 2. Reflect both shaders to populate the set of properties
    ExtractProperties(_vsBytecode);
    ExtractProperties(_psBytecodeFwd);
    ExtractProperties(_psBytecodeDef);

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
            texDesc.textureBindPoint = bindDesc.BindPoint;
            _textureDescs.InsertOrOverwrite(texDesc.textureBindPoint, texDesc);
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