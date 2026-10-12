// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <Memory/UniquePtr.h>

// ------------------------------------------------------------

namespace ost
{
    class Scene;

    class GameContext
    {
    public:
        virtual ~GameContext() = default;

        virtual UniquePtr<Scene> CreateScene(bool makeActive = true) = 0;
        virtual void SetActiveScene(Scene& scene) = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------