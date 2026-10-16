// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Math/Math.h"
#include "Math/Shapes/Shape.h"

// ------------------------------------------------------------

namespace ost
{
    class AABB3D : public Shape3D
    {
    public:
        static AABB3D FromMinAndMax(const Vector3f& min, const Vector3f& max)
        {
            return {min, max};
        }
        static AABB3D FromMinAndSize(const Vector3f& min, const Vector3f& size)
        {
            return {min, min + size};
        }
        static AABB3D FromCenterAndSize(const Vector3f& center, const Vector3f& size)
        {
            const Vector3f halfSize = size * 0.5f;

            return {center - halfSize, center + halfSize};
        }

        const Vector3f& GetMin() const
        {
            return _min;
        }
        const Vector3f& GetMax() const
        {
            return _max;
        }

        Vector3f GetSize() const
        {
            return _max - _min;
        }
        Vector3f GetHalfSize() const
        {
            return GetSize() * 0.5f;
        }

        Vector3f GetCenter() const
        {
            return _min + GetHalfSize();
        }
        Vector3f GetClosestPoint(const Vector3f& p) const
        {
            Vector3f closest = {0, 0, 0};
            closest.X = math::Clamp<Float32>(p.X, _min.X, _max.X);
            closest.Y = math::Clamp<Float32>(p.Y, _min.Y, _max.Y);
            closest.Z = math::Clamp<Float32>(p.Z, _min.Z, _max.Z);
            return closest;
        }

        // BEGIN Shape3D
        bool IsInside(const Vector3f& p) const override
        {
            return (p.X > _min.X && p.X < _max.X) && (p.Y > _min.Y && p.Y < _max.Y) && (p.Z > _min.Z && p.Z < _max.Z);
        }
        // END Shape3D

    private:
        AABB3D(const Vector3f& min, const Vector3f& max)
            : _min{min}
            , _max{max}
        {
        }

        Vector3f _min;
        Vector3f _max;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------