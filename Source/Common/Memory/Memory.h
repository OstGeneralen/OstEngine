// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <OstTypes.h>
#include <cstring>

// ------------------------------------------------------------

namespace ost
{
    inline void MemCopy(void* dst, const void* src, SizeType num)
    {
        memcpy_s(dst, num, src, num);
    }

    inline void MemSet(void* dst, Uint8 value, SizeType num)
    {
        memset(dst, value, num);
    }

    inline void MemZero(void* dst, SizeType num)
    {
        MemSet(dst, 0, num);
    }
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------