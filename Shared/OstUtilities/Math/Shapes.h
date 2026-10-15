// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Math/Vector2.h"
#include "Math/Vector3.h"

// ------------------------------------------------------------

namespace ost
{
    struct Line2D
    {
        Vector2f point;
        Vector2f direction;
    };

    struct Line3D
    {
        Vector3f point;
        Vector3f direction;
    };

    struct Ray2D
    {
        Vector2f origin;
        Vector2f direction;
    };

    struct Ray3D
    {
        Vector3f origin;
        Vector3f direction;
    };

    struct LineSegment2D
    {
        Vector2f startPoint;
        Vector2f endPoint;
    };

    struct LineSegment3D
    {
        Vector3f startPoint;
        Vector3f endPoint;
    };

    struct Plane
    {
        Vector3f point;
        Vector3f normal;
    };

    struct AABB2D
    {
        Vector2f min;
        Vector2f max;
    };

    struct Circle
    {
        Vector2f center;
        Float32 radius;
    };

    struct AABB3D
    {
        Vector3f min;
        Vector3f max;
    };

    struct Sphere
    {
        Vector3f center;
        Float32 radius;
    };

} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------