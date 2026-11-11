// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Container/List.h"

// ------------------------------------------------------------

namespace ost
{
    class BufferView
    {
    public:
        BufferView() = default;
        BufferView(const BufferView&) = default;
        BufferView(const void* pBuf, SizeType sz);
        BufferView(const List<Uint8>& buf);

        BufferView& operator=(const BufferView&) = default;
        BufferView& operator=(std::nullptr_t);
        BufferView& operator=(const List<Uint8>& buf);

        const void* Data() const;
        SizeType Size() const;

        List<Uint8> HardCopy() const;

    private:
        const void* _pBuffer = nullptr;
        SizeType _size = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------