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

HTexture GraphicsResourceManager::CreateTexture(const TextureDesc& data)
{
    Texture created;
    _pRHI->CreateTexture(data, created);
    return HTexture{_textures.Add(std::move(created))};
}

HShader GraphicsResourceManager::CreateShader(const ShaderDesc& desc)
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

HIndexBuffer ost::GraphicsResourceManager::CreateIndexBuffer(const IndexBufferDesc& desc)
{
    Buffer buffer;
    _pRHI->CreateIndexBuffer(desc.numIndices, desc.pIndexData, buffer);
    return HIndexBuffer{_buffers.Add(buffer)};
}

HVertexBuffer GraphicsResourceManager::CreateVertexBuffer(const VertexBufferDesc& desc)
{
    Buffer buffer;
    SizeType vertexSize = 0;
    switch (desc.vertexType)
    {
    case EVertexType::Position:
        vertexSize = sizeof(PositionVertex);
        break;
    case EVertexType::Static:
        vertexSize = sizeof(StaticVertex);
        break;
    case EVertexType::Blit:
        vertexSize = sizeof(BlitVertex);
        break;
    }

    _pRHI->CreateVertexBuffer(vertexSize, desc.numVertices, desc.pVertexData, buffer);

    return HVertexBuffer{_buffers.Add(buffer)};
}

HUniformBuffer ost::GraphicsResourceManager::CreateUniformBuffer(const UniformBufferDesc& desc)
{
    Buffer buffer;
    _pRHI->CreateBuffer(desc.numBytes, buffer, desc.pData);
    return HUniformBuffer{_buffers.Add(buffer)};
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

void GraphicsResourceManager::Release(HVertexBuffer handle)
{
    _buffers.Remove(handle.AsInteger());
}

void GraphicsResourceManager::Release(HIndexBuffer handle)
{
    _buffers.Remove(handle.AsInteger());
}

void GraphicsResourceManager::Release(HUniformBuffer handle)
{
    _buffers.Remove(handle.AsInteger());
}

// ------------------------------------------------------------

const Texture& GraphicsResourceManager::Get(HTexture hnd) const
{
    return _textures[static_cast<Uint64>(hnd)];
}

const Shader& GraphicsResourceManager::Get(HShader hnd) const
{
    return _shaders[static_cast<Uint64>(hnd)];
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------