// Kasper "OstGeneralen" Esbjornsson - 2026
#include "GraphicsResourceManager.h"

#include "RHI/RenderHardwareInterface.h"

using namespace ost;

// ------------------------------------------------------------

void GraphicsResourceManager::Initialize(const RenderHardwareInterface& rhi)
{
    _pRHI = &rhi;
    _materialFactory.Initialize(rhi);
}

// ------------------------------------------------------------

MaterialHandle GraphicsResourceManager::Create(const MaterialDesc& desc)
{
    Material created;
    _materialFactory.CreateMaterial(desc, created);
    return MaterialHandle{_materials.Add(std::move(created))};
}

TextureHandle GraphicsResourceManager::Create(const ResourceTextureDesc& desc)
{
    Texture created;
    _pRHI->CreateTexture(desc, created);
    return TextureHandle{_textures.Add(std::move(created))};
}

ModelHandle GraphicsResourceManager::Create(const StaticModelDesc& desc)
{
    Model created;
    _pRHI->CreateVertexBuffer(sizeof(SurfaceVertex), desc.vertices.GetSize(), desc.vertices.GetData(), created.vertexBuffer);
    _pRHI->CreateIndexBuffer(desc.indices.GetSize(), desc.indices.GetData(), created.indexBuffer);

    SizeType maxMaterialIndex = 0;

    for (const auto& submesh : desc.meshes)
    {
        Mesh createdMesh;
        createdMesh.indexBuffer = created.indexBuffer;
        createdMesh.vertexBuffer = created.vertexBuffer;

        createdMesh.vertexCount = submesh.vertexCount;
        createdMesh.vertexOffset = submesh.vertexOffset;

        createdMesh.indexCount = submesh.indexCount;
        createdMesh.indexOffset = submesh.indexOffset;

        createdMesh.materialIndex = submesh.materialIndex;

        if (createdMesh.materialIndex > maxMaterialIndex)
        {
            maxMaterialIndex = createdMesh.materialIndex;
        }

        created.meshHandles.Add(_meshes.Add(createdMesh));
    }

    created.materials = List<MaterialHandle>(maxMaterialIndex + 1);

    return ModelHandle{_models.Add(created)};
}

// ------------------------------------------------------------

const Texture& GraphicsResourceManager::Get(TextureHandle hnd) const
{
    return _textures[static_cast<SizeType>(hnd)];
}

const Material& GraphicsResourceManager::Get(MaterialHandle hnd) const
{
    return _materials[static_cast<SizeType>(hnd)];
}

const Model& GraphicsResourceManager::Get(ModelHandle hnd) const
{
    return _models[static_cast<SizeType>(hnd)];
}

const Mesh& GraphicsResourceManager::Get(MeshHandle hnd) const
{
    return _meshes[static_cast<SizeType>(hnd)];
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------