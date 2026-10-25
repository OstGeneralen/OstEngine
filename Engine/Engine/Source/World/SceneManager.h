// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/World/ISceneManager.h"

#include <Container/List.h>

// ------------------------------------------------------------

namespace ost
{
    class Scene;
    class SceneGraph;

    class SceneManager : public ISceneManager
    {
    public:
        // BEGIN ISceneManager
        IScene* CreateScene() override;

        void SetActiveScene(IScene* pScene) override;
        IScene* GetActiveScene() override;
        const IScene* GetActiveScene() const override;
        // END ISceneManager

        SceneGraph& GetActiveSceneGraph();
        void Tick(ServiceLocator& serviceLocator);

    private:
        List<Scene*> _scenes;
        SizeType _activeSceneIndex = SizeTypeNpos;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------