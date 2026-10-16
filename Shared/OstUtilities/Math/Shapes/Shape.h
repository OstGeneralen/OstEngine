// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Math/Vector2.h"
#include "Math/Vector3.h"

// ------------------------------------------------------------

namespace ost
{
    class Shape2D
    {
    public:
        virtual ~Shape2D() = default;
        virtual bool IsInside(const Vector2f& p) const = 0;
    };

    class Shape3D
    {
    public:
        virtual ~Shape3D() = default;
        virtual bool IsInside(const Vector3f& p) const = 0;
    };

} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------