// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/World/Actor.h"
#include "Engine/World/Scene.h"

// ------------------------------------------------------------

namespace ost
{
    class ISceneManager
    {
    public:
        virtual Scene* CreateScene() = 0;
        virtual void SetActiveScene(Scene* pScene) = 0;
        virtual Scene* GetActiveScene() = 0;
        virtual const Scene* GetActiveScene() const = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------