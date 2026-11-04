// Kasper "OstGeneralen" Esbjornsson - 2026
#include "GraphicsResourceManager.h"

#include "GraphicsEngine/Rendering/Vertex.h"
#include "RHI/HLSLCompiler.h"
#include "RHI/RenderHardwareInterface.h"

#include <d3d11_1.h>

using namespace ost;

// ------------------------------------------------------------

void GraphicsResourceManager::Initialize(const RenderHardwareInterface& rhi)
{
    _pRHI = &rhi;
}

// ------------------------------------------------------------

HTexture GraphicsResourceManager::Create(const TextureDesc& data)
{
    Texture created;
    _pRHI->CreateTexture(data, created);
    return HTexture{_textures.Add(std::move(created))};
}

HMesh GraphicsResourceManager::Create(const RawVertexData& vertexData, const List<Uint32>& indices)
{
    MeshDesc desc;
    desc.indexCount = indices.GetSize();
    desc.vertexCount = vertexData.GetVertexCount();
    desc.materialIndex = 0;

    const auto meshHandleList = Create(vertexData, indices, List<MeshDesc>{desc});
    return meshHandleList[0];
}

List<HMesh> GraphicsResourceManager::Create(const RawVertexData& vertexData, const List<Uint32>& indices, const List<MeshDesc>& meshDescs)
{
    Buffer vertexBuffer;
    Buffer indexBuffer;

    _pRHI->CreateVertexBuffer(vertexData.GetVertexByteSize(), vertexData.GetVertexCount(), vertexData.GetVertexData(), vertexBuffer);
    _pRHI->CreateIndexBuffer(indices.GetSize(), indices.GetData(), indexBuffer);

    SizeType maxMaterialIndex = 0;

    List<HMesh> meshHandles;

    for (const auto& submesh : meshDescs)
    {
        Mesh createdMesh;
        createdMesh.indexBuffer = indexBuffer;
        createdMesh.vertexBuffer = vertexBuffer;

        createdMesh.vertexOffset = submesh.vertexOffset;
        createdMesh.numIndices = submesh.indexCount;
        createdMesh.indexOffset = submesh.indexOffset;

        createdMesh.materialIndex = submesh.materialIndex;

        meshHandles.Add(HMesh{_meshes.Add(createdMesh)});
    }

    return meshHandles;
}

HShader GraphicsResourceManager::Create(const ShaderDesc& desc)
{
    List<Uint8> bytecode;
    if (desc.precompiled)
    {
        bytecode = desc.code;
    }
    else
    {
        const auto& compileInfo = desc.compileInfo;

        HLSLCompiler compiler;
        bytecode = std::move(compiler.Compile(compileInfo.name, desc.pipelineStage, desc.code, compileInfo.entryPoint, compileInfo.includeRoot));
    }

    Shader created;
    _pRHI->CreateShader(desc.pipelineStage, bytecode, created);

    return HShader{_shaders.Add(created)};
}

// ------------------------------------------------------------

const ITexture& GraphicsResourceManager::GetTexture(HTexture h) const
{
    return _textures[static_cast<Uint64>(h)];
}

const IShader& GraphicsResourceManager::GetShader(HShader h) const
{
    return _shaders[static_cast<Uint64>(h)];
}

// ------------------------------------------------------------

void GraphicsResourceManager::Release(HTexture handle)
{
    _textures.Remove(static_cast<Uint64>(handle));
}

void GraphicsResourceManager::Release(HShader handle)
{
    _shaders.Remove(static_cast<Uint64>(handle));
}

// ------------------------------------------------------------

const Texture& GraphicsResourceManager::Get(HTexture hnd) const
{
    return _textures[static_cast<Uint64>(hnd)];
}

const Mesh& GraphicsResourceManager::Get(HMesh hnd) const
{
    return _meshes[static_cast<Uint64>(hnd)];
}

const Shader& GraphicsResourceManager::Get(HShader hnd) const
{
    return _shaders[static_cast<Uint64>(hnd)];
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------