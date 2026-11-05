// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Resources/IGraphicsResourceManager.h"
#include "GraphicsEngine/Resources/ObjectHandles.h"

// Actual Resource Includes
#include "Objects/Buffer.h"
#include "Objects/PipelineStateObject.h"
#include "Objects/Shader.h"
#include "Objects/Texture.h"

#include <Container/SlotMap.h>

// ------------------------------------------------------------

namespace ost
{
    class RenderHardwareInterface;

    class GraphicsResourceManager : public IGraphicsResourceManager
    {
    public:
        void Initialize(const RenderHardwareInterface& rhi);

        const Texture& Get(HTexture hnd) const;
        const Shader& Get(HShader hnd) const;
        const Buffer& Get(HUniformBuffer hnd) const;
        const Buffer& Get(HVertexBuffer hnd) const;
        const Buffer& Get(HIndexBuffer hnd) const;

        // BEGIN IGraphicsResourceManager
        HTexture CreateTexture(const TextureDesc& desc) override;
        HIndexBuffer CreateIndexBuffer(const IndexBufferDesc& desc) override;
        HVertexBuffer CreateVertexBuffer(const VertexBufferDesc& desc) override;
        HUniformBuffer CreateUniformBuffer(const UniformBufferDesc& desc) override;
        HShader CreateShader(const ShaderDesc& desc) override;

        const ITexture& GetTexture(HTexture h) const override;
        const IShader& GetShader(HShader h) const override;

        void Release(HTexture handle) override;
        void Release(HShader handle) override;
        void Release(HVertexBuffer handle) override;
        void Release(HIndexBuffer handle) override;
        void Release(HUniformBuffer handle) override;
        // END IGraphicsResourceManager

    private:
        SlotMap<Texture> _textures;
        SlotMap<Buffer> _buffers;
        SlotMap<Shader> _shaders;

        const RenderHardwareInterface* _pRHI;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------