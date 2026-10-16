// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Math/Shapes/Shape.h"

// ------------------------------------------------------------

namespace ost
{
    class Plane : public Shape3D
    {
    public:
        static Plane FromPointAndNormal(const Vector3f& p, const Vector3f& n)
        {
            return {p, n};
        }
        static Plane FromPoints(const Vector3f& p1, const Vector3f& p2, const Vector3f& p3)
        {
            const Vector3f e1 = p2 - p1;
            const Vector3f e2 = p3 - p2;

            return {p1, e1.Cross(e2)};
        }


        // BEGIN Shape3D
        bool IsInside(const Vector3f& p) const override
        {
            const Vector3f toP = p - _point;
            return toP.Dot(_normal) > 0.0f;
        }
        // END Shape3D

    private:
        Plane(const Vector3f& p, const Vector3f& n)
            : _point{p}
            , _normal{n.GetNormalized()}
        {
        }

        Vector3f _point;
        Vector3f _normal;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------