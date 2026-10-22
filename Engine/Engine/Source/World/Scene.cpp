// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Engine/World/Scene.h"

#include "Engine/World/Actor.h"

using namespace ost;

// ------------------------------------------------------------

Scene::Scene(GameWorld& world)
    : _actors{}
    , _gameWorld{world}
{
}

Scene::~Scene() = default;

// ------------------------------------------------------------

Actor* Scene::CreateActor()
{
    return _actors.Add(Ptr::NewUnique<Actor>(_gameWorld)).Get();
}

// ------------------------------------------------------------

List<UniquePtr<Actor>>& ost::Scene::GetAllActors()
{
    return _actors;
}

const List<UniquePtr<Actor>>& ost::Scene::GetAllActors() const
{
    return _actors;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------