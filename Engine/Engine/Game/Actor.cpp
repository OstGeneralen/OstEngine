// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Actor.h"

#include "Component.h"
#include "Scene.h"

using namespace ost;

// ------------------------------------------------------------

Actor::Actor(Scene& scene)
    : _scene{&scene}
{
}

Actor::~Actor()
{
}

Component* ost::Actor::GetComponent(TypeID componentType)
{
    if (auto pComp = _components.TryGetValue(componentType))
    {
        return pComp->Get();
    }
    return nullptr;
}

const Component* ost::Actor::GetComponent(TypeID componentType) const
{
    if (auto pComp = _components.TryGetValue(componentType))
    {
        return pComp->Get();
    }
    return nullptr;
}

Component& ost::Actor::AddComponent(TypeID componentType, UniquePtr<Component>&& component)
{
    auto& added = _components.Insert(componentType, std::move(component));
    _pendingLoadComponents.Push( added.Get() );
    return *added;
}

void ost::Actor::SetParent(Actor* parent)
{
    if (parent)
    {
        _transform.SetParent(&parent->_transform);
    }
    else
    {
        _transform.SetParent(nullptr);
    }
    _parent = parent;
}

void Actor::Tick(EngineContext& context)
{
    Component* loadComponent = nullptr;
    while(_pendingLoadComponents.TryPop(loadComponent))
    {
        loadComponent->Start( context );
    }

    for(auto&[type, comp] : _components)
    {
        if(comp->ShouldTick())
        {
            comp->Update( context );
        }
    }
}

Actor* ost::Actor::GetParent()
{
    return _parent;
}

Scene& ost::Actor::GetScene()
{
    return *_scene;
}

Transform& Actor::GetTransform()
{
    return _transform;
}

const Transform& Actor::GetTransform() const
{
    return _transform;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------