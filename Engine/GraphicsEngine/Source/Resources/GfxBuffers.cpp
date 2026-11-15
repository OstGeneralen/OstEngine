// Kasper "OstGeneralen" Esbjornsson - 2026
#include "GfxBuffers.h"

#include "RHI/RHIInternal.h"

#include <Memory/Memory.h>
#include <Utility/Assert.h>

using namespace ost;

// ------------------------------------------------------------
// Uniform Buffer
// ------------------------------------------------------------

DEFINE_GFX_RESOURCE_DEFAULTS(GfxUniformBuffer);

ost::GfxUniformBuffer::GfxUniformBuffer(ComPtr<RHIBuffer>&& rhiResource, SizeType byteSize)
    : _buffer{std::move(rhiResource)}
    , _data(byteSize)
{
}

const RHIBuffer* ost::GfxUniformBuffer::GetRHIPtr() const
{
    return _buffer.Get();
}

SizeType ost::GfxUniformBuffer::GetDataSize() const
{
    return _data.GetSize();
}

void ost::GfxUniformBuffer::SetData(const void* pData, SizeType size)
{
    OST_ASSERT(size <= _data.GetSize(), "SetData size must be equal or less than the total uniform size");
    MemCopy(_data.GetData(), pData, size);
}

const void* ost::GfxUniformBuffer::GetNativeResourcePtr() const
{
    return GetRHIPtr();
}

void ost::GfxUniformBuffer::SetDebugName(const std::string& name) const
{
    if (_buffer)
    {
        _buffer->SetPrivateData(WKPDID_D3DDebugObjectName, static_cast<UINT>(name.length()), name.data());
    }
}

// ------------------------------------------------------------
// Vertex Buffer
// ------------------------------------------------------------

DEFINE_GFX_RESOURCE_DEFAULTS(GfxVertexBuffer);

ost::GfxVertexBuffer::GfxVertexBuffer(ComPtr<RHIBuffer>&& rhiResource, EVertexType vertType, SizeType vertexCount)
    : _buffer{std::move(rhiResource)}
    , _vertexType{vertType}
    , _vertexCount{vertexCount}
{
}

const RHIBuffer* ost::GfxVertexBuffer::GetRHIPtr() const
{
    return _buffer.Get();
}

EVertexType ost::GfxVertexBuffer::GetVertexType() const
{
    return _vertexType;
}

SizeType ost::GfxVertexBuffer::GetVertexSize() const
{
    switch (_vertexType)
    {
    case EVertexType::Position:
        return sizeof(PositionVertex);
    case EVertexType::Static:
        return sizeof(StaticVertex);
    case EVertexType::Blit:
        return sizeof(BlitVertex);
    }

    return 0;
}

SizeType ost::GfxVertexBuffer::GetVertexCount() const
{
    return _vertexCount;
}

const void* ost::GfxVertexBuffer::GetNativeResourcePtr() const
{
    return GetRHIPtr();
}

void ost::GfxVertexBuffer::SetDebugName(const std::string& name) const
{
    if (_buffer)
    {
        _buffer->SetPrivateData(WKPDID_D3DDebugObjectName, static_cast<UINT>(name.length()), name.data());
    }
}

// ------------------------------------------------------------
// Index Buffer
// ------------------------------------------------------------

DEFINE_GFX_RESOURCE_DEFAULTS(GfxIndexBuffer);

ost::GfxIndexBuffer::GfxIndexBuffer(ComPtr<RHIBuffer>&& rhiResource, SizeType indexCount)
    : _buffer{std::move(rhiResource)}
    , _indexCount{indexCount}
{
}

const RHIBuffer* ost::GfxIndexBuffer::GetRHIPtr() const
{
    return _buffer.Get();
}

SizeType ost::GfxIndexBuffer::GetIndexCount() const
{
    return _indexCount;
}

const void* ost::GfxIndexBuffer::GetNativeResourcePtr() const
{
    return GetRHIPtr();
}

void ost::GfxIndexBuffer::SetDebugName(const std::string& name) const
{
    if (_buffer)
    {
        _buffer->SetPrivateData(WKPDID_D3DDebugObjectName, static_cast<UINT>(name.length()), name.data());
    }
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------