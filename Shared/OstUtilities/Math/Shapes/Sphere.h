// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Math/Shapes/Shape.h"

// ------------------------------------------------------------

namespace ost
{
    class Sphere : public Shape3D
    {
    public:
        Sphere(const Vector3f& p, Float32 r)
            : _point{p}
            , _radius{r}
        {
        }

        Vector3f ClosestPoint(const Vector3f& p) const
        {
            if (IsInside(p))
            {
                // If inside, we simply project outwards in the direction to p
                return (p - _point).GetNormalized() * _radius;
            }

            const Vector3f toP = _point - p;
            const Float32 cToP = toP.Magnitude();
            const Float32 s = (cToP - _radius) / cToP;

            return p + (toP * s);
        }

        // BEGIN Shape3D
        bool IsInside(const Vector3f& p) const override
        {
            const Float32 r2 = _radius * _radius;
            const Float32 m2 = (_point - p).MagnitudeSq();
            return m2 < r2;
        }
        // END Shape3D

    private:
        Vector3f _point;
        Float32 _radius;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------