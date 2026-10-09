// Kasper "OstGeneralen" Esbjornsson - 2026
#include "GraphicsResourceManager.h"

#include "GraphicsEngine/Rendering/Vertex.h"
#include "RHI/RenderHardwareInterface.h"

#include <d3d11_1.h>

using namespace ost;

// ------------------------------------------------------------

void GraphicsResourceManager::Initialize(const RenderHardwareInterface& rhi)
{
    _pRHI = &rhi;
}

// ------------------------------------------------------------

TextureHandle GraphicsResourceManager::Create(const TextureCPUData& data)
{
    Texture created;
    _pRHI->CreateTexture(data, created);
    return TextureHandle{_textures.Add(std::move(created))};
}

ModelHandle GraphicsResourceManager::Create(const ModelCPUData& data)
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

    created.materials = List<MaterialHandle>(data.numMaterials);

    return ModelHandle{_models.Add(created)};
}

// ------------------------------------------------------------

void ost::GraphicsResourceManager::Release(TextureHandle handle)
{
    _textures.Remove(static_cast<Uint64>(handle));
}

void ost::GraphicsResourceManager::Release(ModelHandle handle)
{
    _models.Remove(static_cast<Uint64>(handle));
}

// ------------------------------------------------------------

const Texture& GraphicsResourceManager::Get(TextureHandle hnd) const
{
    return _textures[static_cast<Uint64>(hnd)];
}

const Model& GraphicsResourceManager::Get(ModelHandle hnd) const
{
    return _models[static_cast<Uint64>(hnd)];
}

const Mesh& GraphicsResourceManager::Get(MeshHandle hnd) const
{
    return _meshes[static_cast<Uint64>(hnd)];
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------