// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <Math/Color.h>
#include <Math/Vector3.h>
#include <Math/Vector4.h>

// ------------------------------------------------------------

namespace ost
{
    enum class ELightType
    {
        Ambient,
        Directional,
        // Point,
        // Spot,
    };

    struct RenderLight
    {
        ELightType lightType;
        Vector3f direction;
        Color color;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------