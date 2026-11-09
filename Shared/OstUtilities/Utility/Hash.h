// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Container/List.h"

#include <OstTypes.h>
#include <string_view>

// ------------------------------------------------------------

namespace ost
{
    namespace hash
    {
        template <SizeType NumValues>
        constexpr inline Uint64 fnv1a(Uint64 values[NumValues])
        {
            Uint64 hash = 14695981039346656037ULL;
            for (SizeType i = 0; i < NumValues; ++i)
            {
                hash ^= values[i];
                hash *= 1099511628211ULL;
            }
            return hash;
        }

        constexpr inline Uint64 fnv1a(std::string_view s)
        {
            Uint64 hash = 14695981039346656037ULL;
            for (char c : s)
            {
                hash ^= static_cast<uint64_t>(c);
                hash *= 1099511628211ULL;
            }
            return hash;
        }
    } // namespace hash
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------