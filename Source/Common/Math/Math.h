// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <OstTypes.h>
#include <algorithm>
#include <cmath>

// ------------------------------------------------------------

namespace ost
{
    namespace math
    {
        template <typename T>
        inline T Abs(const T& v)
        {
            return std::abs(v);
        }

        template <typename T>
        inline T Min(const T& a, const T& b)
        {
            return std::min<T>(a, b);
        }

        template <typename T>
        inline constexpr T Max(const T& a, const T& b)
        {
            return std::max<T>(a, b);
        }

        template <typename T>
        inline constexpr T Clamp(const T& v, const T& min, const T& max)
        {
            return std::clamp<T>(v, min, max);
        }

        template <typename T>
        inline bool Equals(const T& a, const T& b)
        {
            return a == b;
        }

        template <>
        inline bool Equals<Float32>(const Float32& a, const Float32& b)
        {
            return Abs(a - b) < 0.0001f;
        }
        
        template <>
        inline bool Equals<Float64>(const Float64& a, const Float64& b)
        {
            return Abs(a - b) < 0.000001;
        }
    } // namespace math
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------