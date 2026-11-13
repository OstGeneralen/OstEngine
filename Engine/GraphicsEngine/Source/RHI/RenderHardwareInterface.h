// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/IRenderHardwareInterface.h"
#include "RHI/RHIMinimal.h"

// Render Objects & Resources
#include "Objects/Buffer.h"
#include "Objects/Shader.h"
#include "Objects/StateObjects.h"
#include "Objects/Texture.h"
#include "Objects/TextureSampler.h"

// Descriptors
#include "GraphicsEngine/Resources/Descriptors/TextureDesc.h"
#include "GraphicsEngine/Resources/Descriptors/VertexElement.h"

// Common
#include <Container/List.h>
#include <Math/Color.h>
#include <Math/Vector2.h>
#include <Memory/BufferView.h>

// ------------------------------------------------------------

namespace ost
{
    class RenderHardwareInterface : public IRenderHardwareInterface
    {
    public: // Lifetime
        RenderHardwareInterface();
        ~RenderHardwareInterface();

        bool Initialize(const Vector2u& renderSize, void* winHnd, bool fullscreen = false);
        bool CreateBackbuffer(Texture& outBackbuffer);
        void ResizeBackbuffer(const Vector2u& newSize, Texture& inOutBackbuffer);

    public: // Resource Management
        bool CreateTexture(const TextureDesc& desc, Texture& outTexture) const;
        bool CreateRenderTargetTexture(const Vector2u& dimensions, EDataFormat format, bool allowAsResource, Texture& outTexture) const;
        bool CreateDepthStencilTexture(const Vector2u& dimensions, bool allowAsResource, Texture& outTexture) const;

        void ClearRenderTarget(const Texture& renderTarget, const Color& clearColor = Colors::Black) const;
        void ClearDepthStencil(const Texture& depthStencil, Float32 depth = 1.0f, Uint8 stencil = 0) const;

        bool CreateVertexBuffer(SizeType vertexSize, SizeType numVerts, const void* pData, Buffer& outBuffer) const;
        bool CreateIndexBuffer(SizeType numIndices, const Uint32* pData, Buffer& outBuffer) const;
        bool CreateBuffer(SizeType numBytes, Buffer& outBuffer, const void* pInitialData = nullptr) const;
        bool UpdateBuffer(const Buffer& targetBuffer, const void* pData, SizeType dataSize) const;

        bool CreateBlendState(EBlendMode stateEnum, BlendState& outState) const;
        bool CreateDepthStencilState(EDepthMode depthMode, DepthStencilState& outState) const;

        bool CreateShader(EPipelineStage stage, BufferView bytecode, Shader& outShader) const;
        ComPtr<RHIVertexLayout> CreateVertexLayout(const List<Uint8>& vsBytecode, const List<VertexElement>& vertexElement) const;

        bool CreateSampler(ESamplerAddressMode addressMode, ESamplerType type, TextureSampler& outSampler) const;

    public: // Pipeline State Management
        void SetTexture(const Texture& texture, Uint32 slot, EPipelineStage stageFlag) const;
        void UnsetTextures() const;

        void SetBuffer(const Buffer& texture, Uint32 slot, EPipelineStage stageFlag) const;

        void SetPrimitiveTopology(EPrimitiveTopology topology) const;
        void SetBlendState(const BlendState& blendState) const;
        void SetDepthStencilState(const DepthStencilState& state) const;

        void SetSampler(const TextureSampler& sampler, Uint32 slot) const;
        void SetShader(const Shader& shader, EPipelineStage stage) const;

        void SetRenderTarget(const Texture& renderTarget, const Texture* pDepthTarget = nullptr) const;
        void SetRenderTargets(const Texture* pRenderTargets, SizeType numTargets, const Texture* pDepthTarget = nullptr) const;
        void UnsetRenderTargets() const;

        void SetViewport(const Vector2f& pos, const Vector2f& size) const;

        void SetVertexBuffer(const Buffer& buffer, SizeType vertexSize) const;
        void SetIndexBuffer(const Buffer& buffer) const;
        void Draw(SizeType indexCount, SizeType indexOffset, SizeType vertexOffset) const;

        void Present() const;

    public:
        // BEGIN IRenderHardwareInterface
        ERHIPlatform GetBackendPlatform() const override;

        void* GetNativeDevice() const override;
        void* GetNativeContext() const override;
        // END IRenderHardwareInterface

    private:
        ComPtr<RHIDevice> _device;
        ComPtr<RHIDeviceContext> _immediateContext;
        ComPtr<RHISwapChain> _swapChain;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------