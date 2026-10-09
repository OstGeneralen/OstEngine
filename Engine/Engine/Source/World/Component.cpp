// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Engine/World/Component.h"

#include "World/ComponentInitializer.h"
#include "World/ComponentTicker.h"

using namespace ost;

// ------------------------------------------------------------

void ActorComponent::Initialize(IComponentInitializer& initializer)
{
    _pOwner = &initializer.GetOwningActor();

    if (HasFlag(EComponentFlag::Ticked))
    {
        static_cast<ComponentInitializer&>(initializer).InitializeAsTickedComponent(*this);
    }
    if (HasFlag(EComponentFlag::AssetOwner))
    {
        static_cast<ComponentInitializer&>(initializer).RequestLoad(*this);
    }
}

void ActorComponent::Destroy(IComponentInitializer& initializer)
{
    if (HasFlag(EComponentFlag::Ticked))
    {
        static_cast<ComponentInitializer&>(initializer).DestroyAsTickedComponent(*this);
    }
    if (HasFlag(EComponentFlag::AssetOwner))
    {
        static_cast<ComponentInitializer&>(initializer).RequestUnload(*this);
    }
}

Actor& ActorComponent::GetOwner()
{
    return *_pOwner;
}

const Actor& ActorComponent::GetOwner() const
{
    return *_pOwner;
}

bool ost::ActorComponent::HasFlag(EComponentFlag flag) const
{
    return (static_cast<Uint32>(_flags) & static_cast<Uint32>(flag)) != 0u;
}

void ost::ActorComponent::AddFlag(EComponentFlag flag)
{
    _flags = static_cast<EComponentFlag>(static_cast<Uint32>(_flags) | static_cast<Uint32>(flag));
}

void ActorComponent::InitializeTicked(ComponentTicker& ticker)
{
    _tickHandle = ticker.RegisterTicked(*this);
}

void ActorComponent::DestroyTicked(ComponentTicker& ticker)
{
    ticker.UnregisterTicked(_tickHandle);
    _tickHandle = 0;
}

// ------------------------------------------------------------

void ost::RenderComponent::Initialize(IComponentInitializer& initializer)
{
    ActorComponent::Initialize(initializer);
    initializer.InitializeAsRenderComponent(*this);
}

void ost::RenderComponent::Destroy(IComponentInitializer& initializer)
{
    initializer.DestroyAsRenderComponent(*this);
    ActorComponent::Destroy(initializer);
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------