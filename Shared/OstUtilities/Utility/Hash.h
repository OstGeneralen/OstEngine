// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <OstTypes.h>
#include <string_view>

// ------------------------------------------------------------

namespace ost
{
    namespace hash
    {
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
    } // namespace hashing
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------