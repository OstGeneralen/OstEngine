// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Resources/Managers/IGfxBufferManager.h"
#include "Resources/GfxBuffers.h"

#include <Container/SlotMap.h>

// ------------------------------------------------------------

namespace ost
{
    class RenderHardwareInterface;

    class GfxBufferManager : public IGfxBufferManager
    {
    public:
        GfxBufferManager(const RenderHardwareInterface& rhi);

        // BEGIN IGfxBufferManager
        HUniformBuffer CreateUniformBuffer(SizeType bufferSize, const void* pInitialData = nullptr) override;
        HVertexBuffer CreateVertexBuffer(EVertexType vertexType, const void* pVertexData, SizeType numVertices) override;
        HIndexBuffer CreateIndexBuffer(const Uint32* pIndexData, SizeType numIndices) override;

        const IUniformBuffer* Get(HUniformBuffer hnd) const override;
        const IVertexBuffer* Get(HVertexBuffer hnd) const override;
        const IIndexBuffer* Get(HIndexBuffer hnd) const override;

        void Release(HUniformBuffer& hnd) override;
        void Release(HVertexBuffer& hnd) override;
        void Release(HIndexBuffer& hnd) override;
        // END IGfxBufferManager

    private:
        const RenderHardwareInterface& _rhi;

        SlotMap<GfxUniformBuffer> _uniformBuffers;
        SlotMap<GfxVertexBuffer> _vertexBuffers;
        SlotMap<GfxIndexBuffer> _indexBuffers;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------