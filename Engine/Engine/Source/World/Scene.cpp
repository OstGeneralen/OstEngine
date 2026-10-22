// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Engine/World/Scene.h"

#include "Engine/World/Actor.h"

#include <sstream>

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
    Actor* ptr = _actors.Add(Ptr::NewUnique<Actor>(_gameWorld)).Get();

    std::stringstream nameStream;
    nameStream << "Actor " << _actors.GetSize();
    ptr->SetName(nameStream.str());

    return ptr;
}

void Scene::DestoryActor(Actor* pActor)
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
        _actors[index] = nullptr;
        _actors.Remove(index);
    }
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