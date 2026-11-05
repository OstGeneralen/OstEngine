// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <Container/List.h>
#include <Math/Color.h>
#include <Math/Vector2.h>
#include <Math/Vector3.h>
#include <Math/Vector4.h>

// ------------------------------------------------------------

namespace ost
{
    enum class EVertexType
    {
        Position,
        Static,
        Blit,
    };

    struct PositionVertex
    {
        Vector4f position;
    };

    struct StaticVertex
    {
        Vector4f position;
        Vector3f normal;
        Vector3f tangent;
        Color color;
        Vector2f uv;
    };

    struct BlitVertex
    {
        Vector4f position;
        Vector2f uv;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------