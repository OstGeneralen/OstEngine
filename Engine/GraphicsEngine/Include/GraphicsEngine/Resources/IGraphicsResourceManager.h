// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Rendering/Vertex.h"
#include "GraphicsEngine/Resources/ObjectHandles.h"

// Graphics Data Objects
#include "GraphicsEngine/Resources/Descriptors/BufferDesc.h"
#include "GraphicsEngine/Resources/Descriptors/ShaderDesc.h"
#include "GraphicsEngine/Resources/Descriptors/TextureDesc.h"

#include <Container/List.h>

// ------------------------------------------------------------

namespace ost
{
    struct ITexture;
    struct IShader;

    class IGraphicsResourceManager
    {
    public:
        virtual ~IGraphicsResourceManager() = default;

        virtual HTexture CreateTexture(const TextureDesc& desc) = 0;
        virtual HIndexBuffer CreateIndexBuffer(const IndexBufferDesc& desc) = 0;
        virtual HVertexBuffer CreateVertexBuffer(const VertexBufferDesc& desc) = 0;
        virtual HUniformBuffer CreateUniformBuffer(const UniformBufferDesc& desc) = 0;
        virtual HShader CreateShader(const ShaderDesc& desc) = 0;

        virtual const ITexture& GetTexture(HTexture h) const = 0;
        virtual const IShader& GetShader(HShader h) const = 0;

        virtual void Release(HTexture handle) = 0;
        virtual void Release(HShader handle) = 0;
        virtual void Release(HVertexBuffer handle) = 0;
        virtual void Release(HIndexBuffer handle) = 0;
        virtual void Release(HUniformBuffer handle) = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------