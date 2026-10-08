// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <OstTypes.h>

#include <Memory/UniquePtr.h>

// ------------------------------------------------------------

namespace ost
{
    class GraphicsAssetsManager;
    class Scene;
    class InputReader;

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

        virtual const TimeStructure& Time() const = 0;

        virtual GraphicsAssetsManager& AssetManager() = 0;

        virtual UniquePtr<Scene> CreateScene(bool makeActive) = 0;
        virtual void SetActiveScene(Scene& scene) = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------