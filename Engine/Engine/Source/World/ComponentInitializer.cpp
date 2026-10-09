// Kasper "OstGeneralen" Esbjornsson - 2026
#include "ComponentInitializer.h"

#include "Engine/World/Component.h"
#include "ComponentTicker.h"

using namespace ost;

// ------------------------------------------------------------

ComponentInitializer::ComponentInitializer(Actor& ownerActor, SceneGraph& SceneGraph, ComponentTicker& ticker)
    : _ownerActor{ownerActor}
    , _SceneGraph{SceneGraph}
    , _ticker{ticker}
{
}

// ------------------------------------------------------------

void ComponentInitializer::InitializeAsRenderComponent(RenderComponent& component)
{
    component.InitializeRenderState(_SceneGraph);
}

void ComponentInitializer::DestroyAsRenderComponent(RenderComponent& component)
{
    component.DestroyRenderState(_SceneGraph);
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

void ost::ComponentInitializer::RequestLoad(ActorComponent& component)
{
    component.Load(*_pAssetManager);
}

void ost::ComponentInitializer::RequestUnload(ActorComponent& component)
{
    component.Unload(*_pAssetManager);
}

// ------------------------------------------------------------

Actor& ComponentInitializer::GetOwningActor()
{
    return _ownerActor;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------