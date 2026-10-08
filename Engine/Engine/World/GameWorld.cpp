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
    _renderGraph.ReconcileTransforms();
}

const RenderGraph& GameWorld::GetRenderGraph() const
{
    return _renderGraph;
}

// ------------------------------------------------------------

void GameWorld::RegisterComponent(Actor& actor, ActorComponent& component)
{
    ComponentInitializer initializer{actor, _renderGraph, _ticker};
    component.Initialize(initializer);
}

void GameWorld::UnregisterComponent(Actor& actor, ActorComponent& component)
{
    ComponentInitializer initializer{actor, _renderGraph, _ticker};
    component.Destroy(initializer);
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------