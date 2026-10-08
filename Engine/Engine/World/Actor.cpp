// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Actor.h"

using namespace ost;

// ------------------------------------------------------------

Actor::Actor(WorldContext& worldContext)
    : _worldContext{worldContext}
{
}

// ------------------------------------------------------------

ActorComponent& Actor::AddComponent(TypeID compType, UniquePtr<ActorComponent>&& component)
{
    _worldContext.RegisterComponent(*this, *component);
    return *_components.Insert(compType, std::move(component));
}

void Actor::RemoveComponent(TypeID componentType)
{
    _worldContext.UnregisterComponent(*this, *_components[componentType]);
    _components.Remove(componentType);
}

ActorComponent* Actor::GetComponent(TypeID componentType)
{
    if (auto ppComp = _components.TryGetValue(componentType))
    {
        return ppComp->Get();
    }
    return nullptr;
}

const ActorComponent* Actor::GetComponent(TypeID componentType) const
{
    if (auto ppComp = _components.TryGetValue(componentType))
    {
        return ppComp->Get();
    }
    return nullptr;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------