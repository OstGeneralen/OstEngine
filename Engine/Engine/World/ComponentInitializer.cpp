// Kasper "OstGeneralen" Esbjornsson - 2026
#include "ComponentInitializer.h"

#include "Component.h"
#include "ComponentTicker.h"

using namespace ost;

// ------------------------------------------------------------

ComponentInitializer::ComponentInitializer(Actor& ownerActor, RenderGraph& renderGraph, IComponentTicker& ticker)
    : _ownerActor{ownerActor}
    , _renderGraph{renderGraph}
    , _ticker{ticker}
{
}

// ------------------------------------------------------------

void ComponentInitializer::InitializeAsRenderComponent(RenderComponent& component)
{
    component.InitializeRenderState(_renderGraph);
}

void ComponentInitializer::DestroyAsRenderComponent(RenderComponent& component)
{
    component.DestroyRenderState(_renderGraph);
}

// ------------------------------------------------------------

void ComponentInitializer::InitializeAsTickedComponent(ActorComponent& component)
{
    component.InitializeTicked(_ticker);
}

void ComponentInitializer::DestroyAsTickedComponent(ActorComponent& component)
{
    component.DestroyTicked(_ticker);
}

// ------------------------------------------------------------

Actor& ComponentInitializer::GetOwningActor()
{
    return _ownerActor;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------