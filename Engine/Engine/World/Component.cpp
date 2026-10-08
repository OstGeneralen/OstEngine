// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Component.h"

#include "ComponentInitializer.h"

using namespace ost;

// ------------------------------------------------------------

void ActorComponent::Initialize(ComponentInitializer& initializer)
{
    _pOwner = &initializer.GetOwningActor();

    if (_shouldTick)
    {
        initializer.InitializeAsTickedComponent(*this);
    }
}

void ActorComponent::Destroy(ComponentInitializer& initializer)
{
    if (_shouldTick)
    {
        initializer.DestroyAsTickedComponent(*this);
    }
}

void ActorComponent::Start(ComponentContext& ctx)
{
    // Blank, not required to overload
}

void ActorComponent::Update(ComponentContext& ctx)
{
    // Blank, not required to overload
}

Actor& ActorComponent::GetOwner()
{
    return *_pOwner;
}

const Actor& ActorComponent::GetOwner() const
{
    return *_pOwner;
}

void ActorComponent::InitializeTicked(IComponentTicker& ticker)
{
    _tickHandle = ticker.RegisterTicked(*this);
}

void ActorComponent::DestroyTicked(IComponentTicker& ticker)
{
    ticker.UnregisterTicked(_tickHandle);
    _tickHandle = 0;
}

// ------------------------------------------------------------

void ost::RenderComponent::Initialize(ComponentInitializer& initializer)
{
    ActorComponent::Initialize(initializer);
    initializer.InitializeAsRenderComponent(*this);
}

void ost::RenderComponent::Destroy(ComponentInitializer& initializer)
{
    initializer.DestroyAsRenderComponent(*this);
    ActorComponent::Destroy(initializer);
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------