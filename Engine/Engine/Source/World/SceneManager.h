// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/World/ISceneManager.h"
#include "World/GameWorld.h"

#include <Container/List.h>

// ------------------------------------------------------------

namespace ost
{
    

    class SceneManager : public ISceneManager
    {
    public:
        // BEGIN ISceneManager
        Scene* CreateScene() override;

        void SetActiveScene(Scene* pScene) override;
        // END ISceneManager

        GameWorld& GetGameWorld();
        Scene* GetActiveScene();

    private:
        List<Scene*> _scenes;
        SizeType _activeSceneIndex = List<Scene*>::Npos;
        GameWorld _gameWorld;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------