// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <Math/Vector2.h>

// ------------------------------------------------------------

namespace ost
{
    struct GUIRect
    {
        Vector2f min;
        Vector2f max;

        GUIRect() = default;
        GUIRect(const GUIRect&) = default;

        GUIRect(const Vector2f& mn, const Vector2f& mx)
            : min{mn}
            , max{mx}
        {
        }

        Vector2f GetCenter()
        {
            return min + GetHalfSize();
        }

        Vector2f GetHalfSize() const
        {
            return GetSize() * 0.5f;
        }

        Vector2f GetSize() const
        {
            return max - min;
        }
    };

} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------