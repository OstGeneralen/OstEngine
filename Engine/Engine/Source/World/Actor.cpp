// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Engine/World/Actor.h"

#include "World/GameWorld.h"

using namespace ost;

// ------------------------------------------------------------

Actor::Actor(GameWorld& gameWorld)
    : _gameWorld{gameWorld}
{
}

// ------------------------------------------------------------

ActorComponent& Actor::AddComponent(TypeID compType, UniquePtr<ActorComponent>&& component)
{
    _gameWorld.RegisterComponent(*this, *component);
    return *_components.Insert(compType, std::move(component));
}

void Actor::RemoveComponent(TypeID componentType)
{
    _gameWorld.UnregisterComponent(*this, *_components[componentType]);
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