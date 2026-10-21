// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/World/SceneGraph.h"
#include "World/ComponentTicker.h"

#include <Services/ServiceLocator.h>

// ------------------------------------------------------------

namespace ost
{
    class Actor;

    class GameWorld
    {
    public:
        GameWorld();
        ~GameWorld();

        void Tick(ServiceLocator& services);
        const SceneGraph& GetSceneGraph() const;

        void RegisterComponent(Actor& actor, ActorComponent& component);
        void UnregisterComponent(Actor& actor, ActorComponent& component);

    private:
        ComponentTicker _ticker;
        SceneGraph _sceneGraph;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------