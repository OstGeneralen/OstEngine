// Kasper "OstGeneralen" Esbjornsson - 2026
#include "World/Scene.h"

#include "Engine/World/Actor.h"

#include <sstream>

using namespace ost;

// ------------------------------------------------------------

Scene::Scene()
    : _actors{}
    , _pendingRemovalActors{}
    , _sceneGraph{}
    , _componentTicker{}
    , _nameId{}
{
}

Scene::~Scene() = default;

// ------------------------------------------------------------

Actor* Scene::CreateActor()
{
    Actor* ptr = _actors.Add(Ptr::NewUnique<Actor>(*this)).Get();

    std::stringstream nameStream;
    nameStream << "Actor " << _actors.GetSize();
    ptr->SetName(nameStream.str());

    return ptr;
}

void Scene::DestroyActor(Actor* pActor)
{
    SizeType index = _actors.Npos;
    for (SizeType i = 0; i < _actors.GetSize(); ++i)
    {
        if (_actors[i].Get() == pActor)
        {
            index = i;
            break;
        }
    }

    if (index != _actors.Npos)
    {
        // Move actor into the list of pending removals
        _pendingRemovalActors.Add(std::move(_actors[index]));
        _actors.Remove(index);
    }
}

void ost::Scene::MarkComponentForDestroy(Actor& actor, TypeID componentType)
{
    _pendingComponentRemovals.Add(PendingComponentDestroyEntry{&actor, componentType});
}

// ------------------------------------------------------------

void ost::Scene::Tick(ServiceLocator& serviceLocator)
{
    // 1. Sweep any pending removals and remove them
    for (const auto& pendingComponentRemove : _pendingComponentRemovals)
    {
        pendingComponentRemove.pActor->RemoveComponentImmediate(pendingComponentRemove.componentTypeId);
    }
    _pendingComponentRemovals.Clear();

    _pendingRemovalActors.Clear(); // Simply clearing this will invoke the dtors and thus clear the actor :)

    // 2. Perform the actual tick
    _componentTicker.TickAll(serviceLocator);

    // 3. Reconcile any dirty transforms
    _sceneGraph.ReconcileTransforms();
}

// ------------------------------------------------------------

SceneGraph& ost::Scene::GetSceneGraph()
{
    return _sceneGraph;
}

ComponentTicker& ost::Scene::GetComponentTicker()
{
    return _componentTicker;
}

// ------------------------------------------------------------

List<UniquePtr<Actor>>& ost::Scene::GetActors()
{
    return _actors;
}

const List<UniquePtr<Actor>>& ost::Scene::GetActors() const
{
    return _actors;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------