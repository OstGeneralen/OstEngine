// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/World/Actor.h"
#include "Engine/World/IScene.h"

// ------------------------------------------------------------

namespace ost
{
    class ISceneManager
    {
    public:
        virtual IScene* CreateScene() = 0;
        virtual void SetActiveScene(IScene* pScene) = 0;
        virtual IScene* GetActiveScene() = 0;
        virtual const IScene* GetActiveScene() const = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------