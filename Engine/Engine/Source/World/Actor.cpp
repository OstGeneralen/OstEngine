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

const StringID& ost::Actor::GetName() const
{
    return _name;
}

void Actor::SetName(const std::string& name)
{
    _name = name;
}

// ------------------------------------------------------------

List<ActorComponent*> ost::Actor::GetComponents()
{
    List<ActorComponent*> comps(_components.GetSize());
    SizeType index = 0;
    for (auto& [type, compPtr] : _components)
    {
        comps[index] = compPtr.Get();
        index++;
    }
    return comps;
}

List<const ActorComponent*> ost::Actor::GetComponents() const
{
    List<const ActorComponent*> comps(_components.GetSize());
    SizeType index = 0;
    for (auto& [type, compPtr] : _components)
    {
        comps[index] = compPtr.Get();
        index++;
    }
    return comps;
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