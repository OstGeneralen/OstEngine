// Kasper "OstGeneralen" Esbjornsson - 2026
#include "MaterialFactory.h"

#include "Objects/Material.h"
#include "RHI/RenderHardwareInterface.h"
#include "Rendering/RenderPipelineConstants.h"

#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <dxgi.h>

#include <filesystem>
#include <fstream>
#include <sstream>

using namespace ost;

// ------------------------------------------------------------

namespace ost::MaterialFactoryInternal
{
    Blob LoadMaterialShaderFileBlob(const std::string& path)
    {
        std::ifstream readStream{path};

        std::stringstream contentStream;
        contentStream << readStream.rdbuf();

        const std::string contentString = contentStream.str();

        return Blob(contentString.data(), contentString.size());
    }

    class MaterialIncludeManager : public ID3DInclude
    {
    public:
        std::string _materialShaderPath;

        MaterialIncludeManager(const std::string& materialShaderPath)
            : _materialShaderPath{materialShaderPath}
        {
        }

        HRESULT Open(D3D_INCLUDE_TYPE incType, LPCSTR includeName, LPCVOID parentData, LPCVOID* ppData, UINT* pBytes) override
        {
            std::string includeNameStr = includeName;

            std::filesystem::path finalIncludePath;

            if (includeNameStr == "EngineMaterial.hlsli")
            {
                // If this is the material include, we simply replace it with the content of the provided material shader path
                finalIncludePath = _materialShaderPath;
            }
            else
            {
                // Otherwise, treat this include as being rooted in the Engine Shaders directory
                finalIncludePath = std::filesystem::path("EngineAssets/Shaders") / includeNameStr;
            }

            // Now we can go ahead and actually load the data :)
            std::ifstream readStream{finalIncludePath, std::ios::ate};
            SizeType bufferSize = readStream.tellg();
            char* buffer = new char[bufferSize];
            readStream.seekg(0);
            readStream.read(buffer, bufferSize);

            (*ppData) = buffer;
            (*pBytes) = bufferSize;
        }

        HRESULT Close(LPCVOID pData) override
        {
            const char* pBuffer = reinterpret_cast<const char*>(pData);
            delete[] pBuffer;
        }
    };
} // namespace ost::MaterialFactoryInternal

// ------------------------------------------------------------

MaterialFactory::MaterialFactory()
    : _rootMaterialSourceCode{}
    , _pRHI{nullptr}
{
}

MaterialFactory::~MaterialFactory() = default;

// ------------------------------------------------------------

void ost::MaterialFactory::Initialize(const RenderHardwareInterface& rhi)
{
    _pRHI = &rhi;

    auto& surfaceShaders = _rootMaterialSourceCode.Insert(EMaterialDomain::Surface, {});
    surfaceShaders.Insert(EMaterialShadingModel::Lit, MaterialFactoryInternal::LoadMaterialShaderFileBlob("EngineAssets/Shaders/LitSurfaceShader.hlsl"));
    surfaceShaders.Insert(EMaterialShadingModel::Unlit, MaterialFactoryInternal::LoadMaterialShaderFileBlob("EngineAssets/Shaders/UnlitSurfaceShader.hlsl"));
}

bool MaterialFactory::CreateMaterial(const MaterialDesc& desc, Material& outMaterial)
{
    // Compile the vertex and pixel shader of the material
    MaterialFactoryInternal::MaterialIncludeManager includeHandler{desc.materialShaderFilePath};
    const Blob& sourceCode = _rootMaterialSourceCode[desc.domain][desc.shadingModel];

    ComPtr<ID3DBlob> vsBlob;
    ComPtr<ID3DBlob> psBlob;
    ComPtr<ID3DBlob> errBlob;
    D3DCompile(sourceCode.Data(), sourceCode.Size(), NULL, NULL, &includeHandler, "VSMain", "vs_4_1", D3DCOMPILE_DEBUG, 0, &vsBlob, &errBlob);
    D3DCompile(sourceCode.Data(), sourceCode.Size(), NULL, NULL, &includeHandler, "PSMain", "vs_4_1", D3DCOMPILE_DEBUG, 0, &psBlob, &errBlob);

    // Create the pipeline state object of the material
    PipelineStateObjectDesc psoDesc;
    psoDesc.vertexShader.pBytecode = vsBlob->GetBufferPointer();
    psoDesc.vertexShader.bytecodeSize = vsBlob->GetBufferSize();

    psoDesc.pixelShader.pBytecode = psBlob->GetBufferPointer();
    psoDesc.pixelShader.bytecodeSize = psBlob->GetBufferSize();

    psoDesc.primitiveTopology = EPrimitiveTopology::TriangleList;

    psoDesc.vertexLayout = List<VertexElement>{5};
    psoDesc.vertexLayout[0] = {"POSITION", EDataSize::Float4};
    psoDesc.vertexLayout[1] = {"NORMAL", EDataSize::Float3};
    psoDesc.vertexLayout[2] = {"TANGENT", EDataSize::Float3};
    psoDesc.vertexLayout[3] = {"COLOR", EDataSize::Float4};
    psoDesc.vertexLayout[4] = {"TEXCOORD", EDataSize::Float2};

    _pRHI->CreatePSO(psoDesc, outMaterial._pso);

    // Reflect and calculate the properties of this material (might not contain any)
    ReflectMaterialProperties(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), outMaterial);
    ReflectMaterialProperties(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), outMaterial);

    _pRHI->CreateBuffer(outMaterial.GetVariablesByteCount(), outMaterial._variablesBuffer);
}

// ------------------------------------------------------------

void ost::MaterialFactory::ReflectMaterialProperties(const void* pBytecode, SizeType bytecodeSize, Material& intoMaterial)
{
    ComPtr<ID3D11ShaderReflection> reflection;
    D3DReflect(pBytecode, bytecodeSize, IID_PPV_ARGS(&reflection));

    auto pPropertiesBuffer = reflection->GetConstantBufferByIndex(PipelineConstant::Get(EBufferSlot::MaterialProperties));

    if (pPropertiesBuffer)
    {
        D3D11_SHADER_BUFFER_DESC desc = {};
        pPropertiesBuffer->GetDesc(&desc);
        const SizeType numVariables = desc.Variables;

        for (SizeType i = 0; i < numVariables; ++i)
        {
            auto pVariable = pPropertiesBuffer->GetVariableByIndex(i);
            D3D11_SHADER_VARIABLE_DESC varDesc = {};
            pVariable->GetDesc(&varDesc);

            if (intoMaterial._propertyMap.Contains(varDesc.Name))
            {
                // We might get overlap between the PS & VS so skip if we've already processed this var
                continue;
            }

            auto& property = intoMaterial._propertyMap.Insert(varDesc.Name, {});
            property.offset = varDesc.StartOffset;
            property.size = varDesc.Size;
            property.type = Material::Property::EType::Variable;

            if (intoMaterial._variablesByteCount < (property.offset + property.size))
            {
                intoMaterial._variablesByteCount = property.offset + property.size;
            }
        }
    }

    const Uint32 materialTexturesStartIndex = PipelineConstant::Get(ETextureSlot::Material0);
    const Uint32 materialTextureEndIndex = PipelineConstant::Get(ETextureSlot::Material7);

    for (Uint32 i = 0; i < materialTextureEndIndex; ++i)
    {
        D3D11_SHADER_INPUT_BIND_DESC texDesc = {};
        if (reflection->GetResourceBindingDesc(i, &texDesc) != S_OK)
        {
            break;
        }

        if (!texDesc.Dimension == D3D11_SRV_DIMENSION_TEXTURE2D)
        {
            continue;
        }

        if (intoMaterial._propertyMap.Contains(texDesc.Name))
        {
            // We might get overlap between the PS & VS so skip if we've already processed this var
            continue;
        }

        auto& property = intoMaterial._propertyMap.Insert(texDesc.Name, {});
        property.offset = texDesc.BindPoint;
        property.size = 0;
        property.type = Material::Property::EType::Texture;

        intoMaterial._numTextures++;
    }
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------