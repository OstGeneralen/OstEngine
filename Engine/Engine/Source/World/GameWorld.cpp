// Kasper "OstGeneralen" Esbjornsson - 2026
#include "GameWorld.h"

#include "ComponentInitializer.h"

// ------------------------------------------------------------

using namespace ost;

// ------------------------------------------------------------

GameWorld::GameWorld()
{
}

GameWorld::~GameWorld()
{
}

void GameWorld::Tick(ComponentContext& context)
{
    _ticker.TickAll(context);
    _sceneGraph.ReconcileTransforms();
}

const SceneGraph& GameWorld::GetSceneGraph() const
{
    return _sceneGraph;
}

// ------------------------------------------------------------

void GameWorld::RegisterComponent(Actor& actor, ActorComponent& component)
{
    ComponentInitializer initializer{actor, _sceneGraph, _ticker};
    component.Initialize(initializer);
}

void GameWorld::UnregisterComponent(Actor& actor, ActorComponent& component)
{
    ComponentInitializer initializer{actor, _sceneGraph, _ticker};
    component.Destroy(initializer);
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------