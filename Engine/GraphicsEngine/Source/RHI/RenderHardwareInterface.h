// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "RHI/RHIMinimal.h"

// Render Objects & Resources
#include "Objects/Buffer.h"
#include "Objects/Model.h"
#include "Objects/PipelineStateObject.h"
#include "Objects/Texture.h"

// Graphics Object Creation Data
#include "GraphicsEngine/Resources/ModelCPUData.h"
#include "GraphicsEngine/Resources/TextureCPUData.h"

// Common
#include <Container/List.h>
#include <Math/Color.h>
#include <Math/Vector2.h>

// ------------------------------------------------------------

namespace ost
{
    class RenderHardwareInterface
    {
    public: // Lifetime
        RenderHardwareInterface();
        ~RenderHardwareInterface();

        bool Initialize(const Vector2u& renderSize, void* winHnd);
        bool CreateBackbuffer( Texture& outBackbuffer );
        void ResizeBackbuffer(const Vector2u& newSize, Texture& inOutBackbuffer);

    public: // Resource Management
        bool CreateTexture(const TextureCPUData& desc, Texture& outTexture) const;
        bool CreateRenderTargetTexture(const Vector2u& dimensions, EDataFormat format, bool allowAsResource, Texture& outTexture) const;
        bool CreateDepthStencilTexture(const Vector2u& dimensions, bool allowAsResource, Texture& outTexture) const;

        void ClearRenderTarget(const Texture& renderTarget, const Color& clearColor = Colors::Black) const;
        void ClearDepthStencil(const Texture& depthStencil, Float32 depth = 1.0f, Uint8 stencil = 0) const;

        bool CreateVertexBuffer(SizeType vertexSize, SizeType numVerts, const void* pData, Buffer& outBuffer) const;
        bool CreateIndexBuffer(SizeType numIndices, const Uint32* pData, Buffer& outBuffer) const;
        bool CreateBuffer(SizeType numBytes, Buffer& outBuffer, const void* pInitialData = nullptr) const;
        bool UpdateBuffer(const Buffer& targetBuffer, const void* pData, SizeType dataSize) const;

        bool CreatePSO(const PipelineStateObjectDesc& desc, PipelineStateObject& outPSO) const;

    public: // Pipeline State Management
        void SetTexture(const Texture& texture, Uint32 slot, EPipelineStage_ stageFlag) const;
        void SetBuffer(const Buffer& texture, Uint32 slot, EPipelineStage_ stageFlag) const;

        void SetPSO(const PipelineStateObject& pso) const;

        void SetRenderTarget(const Texture& renderTarget, const Texture* pDepthTarget = nullptr) const;
        void SetRenderTargets(const Texture* pRenderTargets, SizeType numTargets, const Texture* pDepthTarget = nullptr) const;

        void Draw( const Mesh& mesh, bool uploadBuffers ) const;

        void Present() const;

    private:
        ComPtr<RHIDevice> _device;
        ComPtr<RHIDeviceContext> _immediateContext;
        ComPtr<RHISwapChain> _swapChain;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------