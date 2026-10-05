// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <Math/Vector2.h>
#include <Math/Vector3.h>
#include <Math/Vector4.h>
#include <Math/Color.h>

// ------------------------------------------------------------

namespace ost
{
    struct SurfaceVertex
    {
        Vector4f position;
        Vector3f normal;
        Vector3f tangent;
        Color color;
        Vector2f uv;
    };
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------