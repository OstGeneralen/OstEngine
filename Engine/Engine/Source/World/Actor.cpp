// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Engine/World/Actor.h"

#include "Engine/IOstEngine.h"
#include "World/ComponentFactory.h"
#include "World/ComponentInitializer.h"
#include "World/Scene.h"

#include <OstLog.h>

using namespace ost;

// ------------------------------------------------------------

auto ActorLog = Log::NewCategory("Actor");

// ------------------------------------------------------------

Actor::Actor(Scene& scene)
    : _scene{scene}
{
}

ost::Actor::~Actor()
{
    ComponentInitializer initializer{*this, _scene.GetSceneGraph(), _scene.GetComponentTicker()};
    for (auto& [type, comp] : _components)
    {
        comp->Destroy(initializer);
    }
    _components.Clear();
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

List<ComponentData> ost::Actor::GetComponents()
{
    List<ComponentData> comps(_components.GetSize());
    SizeType index = 0;
    for (auto& [type, compPtr] : _components)
    {
        comps[index].componentTypeID = type;
        comps[index].pComponent = compPtr.Get();
        index++;
    }
    return comps;
}

// ------------------------------------------------------------

ActorComponent& Actor::AddComponent(TypeID compType)
{
    IComponentFactory& factoryInterface = pEngine->GetServiceLocator().GetRequired<IComponentFactory>();
    ComponentFactory& factory = static_cast<ComponentFactory&>(factoryInterface);

    UniquePtr<ActorComponent> component = factory.CreateComponentFromType(compType);

    // Initialize the component
    ComponentInitializer initializer(*this, _scene.GetSceneGraph(), _scene.GetComponentTicker());
    component->Initialize(initializer);

    return *_components.Insert(compType, std::move(component));
}

void Actor::RemoveComponent(TypeID componentType)
{
    _scene.MarkComponentForDestroy(*this, componentType);
}

void ost::Actor::RemoveComponentImmediate(TypeID componentType)
{
    if (UniquePtr<ActorComponent>* pFound = _components.TryGetValue(componentType))
    {
        ActorComponent* pComp = pFound->Get();

        ComponentInitializer initializer(*this, _scene.GetSceneGraph(), _scene.GetComponentTicker());
        pComp->Destroy(initializer);
        (*pFound) = nullptr;

        _components.Remove(componentType);
    }
    else
    {
        Log::Warning(ActorLog, "Actor '{}' unable to remove component of type id '{}'. Not found.", _name.GetString(), static_cast<SizeType>(componentType));
    }
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