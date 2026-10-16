// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Math/Shapes/Shape.h"

// ------------------------------------------------------------

namespace ost
{
    class Line2D : public Shape2D
    {
    public:
        static Line2D FromPointAndNormal(const Vector2f& p, const Vector2f& n)
        {
            return {p, {n.Y, -n.X}};
        }
        static Line2D FromPointAndDirection(const Vector2f& p, const Vector2f& d)
        {
            return Line2D{p, d};
        }
        static Line2D FromPoints(const Vector2f& p1, const Vector2f& p2)
        {
            return FromPointAndDirection(p1, p2 - p1);
        }

        const Vector2f& GetDirection() const
        {
            return _direction;
        }

        Vector2f GetNormal() const
        {
            return Vector2f{-_direction.Y, _direction.X};
        }

        // Shape2D
        bool IsInside(const Vector2f& p) const override
        {
            const Vector2f toP = Vector2f{p - _point};
            return toP.Dot(_direction) > 0.0f;
        }

    private:
        Line2D(const Vector2f& p, const Vector2f& d)
            : _point{p}
            , _direction{d.GetNormalized()}
        {
        }

        Vector2f _point = {0, 0};
        Vector2f _direction = {0, 1};
    };

    class Line3D
    {
    public:
        static Line3D FromPointAndDirection(const Vector3f& p, const Vector3f& d)
        {
            return {p, d};
        }
        static Line3D FromPoints(const Vector3f& p1, const Vector3f& p2)
        {
            return FromPointAndDirection(p1, p2 - p1);
        }

        const Vector3f& GetDirection() const
        {
            return _direction;
        }

    private:
        Line3D(const Vector3f& p, const Vector3f& d)
            : _point{p}
            , _direction{d.GetNormalized()}
        {
        }

        Vector3f _point = {0, 0, 0};
        Vector3f _direction = {1, 0, 0};
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------