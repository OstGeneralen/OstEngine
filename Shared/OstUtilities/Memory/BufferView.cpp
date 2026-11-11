// Kasper "OstGeneralen" Esbjornsson - 2026
#include "BufferView.h"

#include "Memory/Memory.h"

using namespace ost;

// ------------------------------------------------------------

ost::BufferView::BufferView(const void* pBuf, SizeType sz)
    : _pBuffer{pBuf}
    , _size{sz}
{
}

ost::BufferView::BufferView(const List<Uint8>& buf)
    : BufferView{buf.GetData(), buf.GetSize()}
{
}

// ------------------------------------------------------------

BufferView& ost::BufferView::operator=(std::nullptr_t)
{
    _pBuffer = nullptr;
    _size = 0;
    return *this;
}

BufferView& ost::BufferView::operator=(const List<Uint8>& buf)
{
    _pBuffer = buf.GetData();
    _size = buf.GetSize();
    return *this;
}

// ------------------------------------------------------------

const void* ost::BufferView::Data() const
{
    return _pBuffer;
}

SizeType ost::BufferView::Size() const
{
    return _size;
}

// ------------------------------------------------------------

List<Uint8> ost::BufferView::HardCopy() const
{
    List<Uint8> cpy(_size);
    MemCopy(cpy.GetData(), _pBuffer, _size);
    return cpy;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------