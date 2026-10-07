// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <OstTypes.h>

// ------------------------------------------------------------

namespace ost
{
    class GraphicsAssetsManager;
    class Scene;

    struct TimeStructure
    {
        Float32 deltaTime;
        Float32 clampedDeltaTime;
        Float64 totalTime;
    };

    class EngineContext
    {
    public:
        virtual ~EngineContext() = default;

        virtual GraphicsAssetsManager& GetAssetManager() = 0;
        virtual const TimeStructure& GetTime() const = 0;
        virtual Scene& GetScene() = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------