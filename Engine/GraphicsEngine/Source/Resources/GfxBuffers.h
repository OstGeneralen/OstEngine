// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Resources/Buffers.h"
#include "RHI/RHIMinimal.h"
#include "Resources/GfxResourceHelper.h"

#include <Container/List.h>

// ------------------------------------------------------------

namespace ost
{
    struct GfxUniformBuffer : public IUniformBuffer
    {
    public:
        DECLARE_GFX_RESOURCE_DEFAULTS(GfxUniformBuffer);

        GfxUniformBuffer(ComPtr<RHIBuffer>&& rhiResource, SizeType byteSize);

        const RHIBuffer* GetRHIPtr() const;

        // BEGIN IUniformBuffer
        SizeType GetDataSize() const override;
        void SetData(const void* pData, SizeType size) override;
        // END IUniformBuffer

        // BEGIN IGraphicsResource
        const void* GetNativeResourcePtr() const override;
        void SetDebugName(const std::string& name) const override;
        // END IGraphicsResource

    private:
        ComPtr<RHIBuffer> _buffer;
        List<Uint8> _data;
    };

    // ------------------------------------------------------------

    struct GfxVertexBuffer : public IVertexBuffer
    {
    public:
        DECLARE_GFX_RESOURCE_DEFAULTS(GfxVertexBuffer);

        GfxVertexBuffer(ComPtr<RHIBuffer>&& rhiResource, EVertexType vertType, SizeType vertexCount);

        const RHIBuffer* GetRHIPtr() const;

        // BEGIN IVertexBuffer
        EVertexType GetVertexType() const override;
        SizeType GetVertexSize() const override;
        SizeType GetVertexCount() const override;
        // END IVertexBuffer

        // BEGIN IGraphicsResource
        const void* GetNativeResourcePtr() const override;
        void SetDebugName(const std::string& name) const override;
        // END IGraphicsResource

    private:
        ComPtr<RHIBuffer> _buffer;
        EVertexType _vertexType = EVertexType::Position;
        SizeType _vertexCount = 0;
    };

    // ------------------------------------------------------------

    struct GfxIndexBuffer : public IIndexBuffer
    {
    public:
        DECLARE_GFX_RESOURCE_DEFAULTS(GfxIndexBuffer);

        GfxIndexBuffer(ComPtr<RHIBuffer>&& rhiResource, SizeType indexCount);

        const RHIBuffer* GetRHIPtr() const;

        // BEGIN IVertexBuffer
        SizeType GetIndexCount() const override;
        // END IVertexBuffer

        // BEGIN IGraphicsResource
        const void* GetNativeResourcePtr() const override;
        void SetDebugName(const std::string& name) const override;
        // END IGraphicsResource

    private:
        ComPtr<RHIBuffer> _buffer;
        SizeType _indexCount = 0;
    };

} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------