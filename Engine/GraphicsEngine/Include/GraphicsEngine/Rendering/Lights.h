// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <OstTypes.h>

#include <Math/Color.h>
#include <Math/Vector3.h>
#include <Memory/Memory.h>

// ------------------------------------------------------------

namespace ost
{
    enum class ELightType
    {
        Unknown,
        Directional,
        Spot,
        Point,
    };

    struct LightData
    {
        ELightType type;
        Color color;
        Float32 intensity;
        Vector3f direction;
        Vector3f position;
        Float32 radius;
        Float32 outerRadius;
        Float32 range;
    };

    struct LightCommand
    {
        LightData cmdData;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------