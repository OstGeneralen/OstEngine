// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/World/ComponentContext.h"
#include "Engine/World/SceneGraph.h"
#include "Engine/World/WorldContext.h"
#include "World/ComponentTicker.h"

// ------------------------------------------------------------

namespace ost
{
    class GameWorld : public WorldContext
    {
    public:
        GameWorld();
        ~GameWorld();

        void Tick(ComponentContext& context);
        const SceneGraph& GetSceneGraph() const;

    public:
        void RegisterComponent(Actor& actor, ActorComponent& component) override;
        void UnregisterComponent(Actor& actor, ActorComponent& component) override;

    private:
        ComponentTicker _ticker;
        SceneGraph _sceneGraph;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------