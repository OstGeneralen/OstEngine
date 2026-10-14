// Kasper "OstGeneralen" Esbjornsson - 2026
#include "GraphicsResourceManager.h"

#include "GraphicsEngine/Rendering/Vertex.h"
#include "RHI/RenderHardwareInterface.h"

#include <d3d11_1.h>

// Materials
#include "Materials/MaterialCompiler.h"

using namespace ost;

// ------------------------------------------------------------

void GraphicsResourceManager::Initialize(const RenderHardwareInterface& rhi)
{
    _pRHI = &rhi;
}

// ------------------------------------------------------------

HTexture GraphicsResourceManager::Create(const TextureCPUData& data)
{
    Texture created;
    _pRHI->CreateTexture(data, created);
    return HTexture{_textures.Add(std::move(created))};
}

HModel GraphicsResourceManager::Create(const ModelCPUData& data)
{
    Model created;

    if (data.vertexLayoutMask & EModelVertexData_StaticMesh)
    {
        List<SurfaceVertex> vertices{data.vertexList.GetSize()};
        for (SizeType i = 0; i < vertices.GetSize(); ++i)
        {
            vertices[i].position = data.vertexList[i].position;
            vertices[i].normal = data.vertexList[i].normal;
            vertices[i].tangent = data.vertexList[i].tangent;
            vertices[i].uv = data.vertexList[i].uv;
            vertices[i].color = data.vertexList[i].color;
        }

        _pRHI->CreateVertexBuffer(sizeof(SurfaceVertex), vertices.GetSize(), vertices.GetData(), created.vertexBuffer);
    }
    else
    {
        OST_ASSERT(false, "UNSUPPORTED VERTEX TYPE!");
    }

    _pRHI->CreateIndexBuffer(data.indexList.GetSize(), data.indexList.GetData(), created.indexBuffer);

    SizeType maxMaterialIndex = 0;

    for (const auto& submesh : data.submeshes)
    {
        Mesh createdMesh;
        createdMesh.indexBuffer = created.indexBuffer;
        createdMesh.vertexBuffer = created.vertexBuffer;

        createdMesh.vertexCount = submesh.vertices.count;
        createdMesh.vertexOffset = submesh.vertices.offset;

        createdMesh.indexCount = submesh.indices.count;
        createdMesh.indexOffset = submesh.indices.offset;

        createdMesh.materialIndex = submesh.materialIndex;

        if (createdMesh.materialIndex > maxMaterialIndex)
        {
            maxMaterialIndex = createdMesh.materialIndex;
        }

        created.meshHandles.Add(_meshes.Add(createdMesh));
    }

    created.materials = List<HMaterial>(data.numMaterials);

    return HModel{_models.Add(created)};
}

// ------------------------------------------------------------

void GraphicsResourceManager::Release(HTexture handle)
{
    _textures.Remove(static_cast<Uint64>(handle));
}

void GraphicsResourceManager::Release(HModel handle)
{
    _models.Remove(static_cast<Uint64>(handle));
}

// ------------------------------------------------------------

const Texture& GraphicsResourceManager::Get(HTexture hnd) const
{
    return _textures[static_cast<Uint64>(hnd)];
}

const Model& GraphicsResourceManager::Get(HModel hnd) const
{
    return _models[static_cast<Uint64>(hnd)];
}

const Mesh& GraphicsResourceManager::Get(HMesh hnd) const
{
    return _meshes[static_cast<Uint64>(hnd)];
}

const Material& GraphicsResourceManager::Get(HMaterial hnd) const
{
    return _materials[static_cast<Uint64>(hnd)];
}

const MaterialInstance& ost::GraphicsResourceManager::Get(HMaterialInstance hnd) const
{
    return _materialInstances[static_cast<Uint64>(hnd)];
}

// ------------------------------------------------------------
// Material Manager
// ------------------------------------------------------------

HMaterial GraphicsResourceManager::CreateMaterial(const MaterialDesc& desc)
{
    MaterialCompiler compiler(desc);
    if (compiler.Compile() == false)
    {
        // Error
        return {};
    }

    Material created;

    BackendMaterialDesc compiledMaterialDesc;
    compiledMaterialDesc.properties = compiler.GetCompiledPropertySet();
    compiledMaterialDesc.textureDescs = compiler.GetCompiledTextureDescs();
    _pRHI->CreatePSO(compiler.GetCompiledPSODescForward(), compiledMaterialDesc.psoFwd);
    _pRHI->CreatePSO(compiler.GetCompiledPSODescDeferred(), compiledMaterialDesc.psoDef);

    created.Create(compiledMaterialDesc);

    return HMaterial{_materials.Add(std::move(created))};
}

HMaterialInstance GraphicsResourceManager::CreateInstance(HMaterial fromMaterialHandle)
{
    MaterialInstance matInstance;

    const Material& rootMaterial = Get(fromMaterialHandle);

    MaterialInstanceDesc desc = {};
    desc.baseMaterialHandle = fromMaterialHandle;

    SizeType bufferSize = rootMaterial.GetPropertiesBufferSize();
    if(bufferSize == 0)
    {
        bufferSize = 16;
    }
    _pRHI->CreateBuffer( bufferSize, desc.propertyBuffer);
    desc.propertyBuffer.SetDebugName( "MaterialProperties" );

    matInstance.Create(desc);
    rootMaterial.PopulateInstanceProperties(matInstance);

    return HMaterialInstance{_materialInstances.Add(std::move(matInstance))};
}

// ------------------------------------------------------------

IMaterial& GraphicsResourceManager::GetMaterial(HMaterial handle)
{
    return _materials[static_cast<Uint64>(handle)];
}

const IMaterial& GraphicsResourceManager::GetMaterial(HMaterial handle) const
{
    return _materials[static_cast<Uint64>(handle)];
}

IMaterialInstance& GraphicsResourceManager::GetMaterialInstance(HMaterialInstance handle)
{
    return _materialInstances[static_cast<Uint64>(handle)];
}

const IMaterialInstance& GraphicsResourceManager::GetMaterialInstance(HMaterialInstance handle) const
{
    return _materialInstances[static_cast<Uint64>(handle)];
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------