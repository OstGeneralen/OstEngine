// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Math/Shapes/Line.h"
#include "Math/Shapes/Shape.h"

// ------------------------------------------------------------

namespace ost
{
    template <typename TVec>
    class RayGeneric
    {
    public:
        static inline RayGeneric FromOriginAndDirection(const TVec& o, const TVec& d)
        {
            return {o, d};
        }
        static inline RayGeneric FromPoints(const TVec& p1, const TVec& p2)
        {
            return FromOriginAndDirection(p1, p2 - p1);
        }

        TVec GetPointAtDistance(Float32 t) const
        {
            return _origin + (_direction * t);
        }

    private:
        RayGeneric(const TVec& o, const TVec& d)
            : _origin{o}
            , _direction{d.GetNormalized()}
        {
        }

        TVec _origin;
        TVec _direction;
    };

    using Ray2D = RayGeneric<Vector2f>;
    using Ray3D = RayGeneric<Vector3f>;
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------