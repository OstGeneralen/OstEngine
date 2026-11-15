// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Resources/Buffers.h"

// ------------------------------------------------------------

namespace ost
{
    class IGfxBufferManager
    {
    public:
        virtual HUniformBuffer CreateUniformBuffer(SizeType bufferSize, const void* pInitialData = nullptr) = 0;
        virtual HVertexBuffer CreateVertexBuffer(EVertexType vertexType, const void* pVertexData, SizeType numVertices) = 0;
        virtual HIndexBuffer CreateIndexBuffer(const Uint32* pIndexData, SizeType numIndices) = 0;

        virtual const IUniformBuffer* Get(HUniformBuffer hnd) const = 0;
        virtual const IVertexBuffer* Get(HVertexBuffer hnd) const = 0;
        virtual const IIndexBuffer* Get(HIndexBuffer hnd) const = 0;

        virtual void Release(HUniformBuffer& hnd) = 0;
        virtual void Release(HVertexBuffer& hnd) = 0;
        virtual void Release(HIndexBuffer& hnd) = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------