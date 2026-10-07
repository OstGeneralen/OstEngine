// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Scene.h"

#include "Actor.h"
#include "Engine/EngineContext.h"

// ------------------------------------------------------------

using namespace ost;

// ------------------------------------------------------------

Scene::Scene() = default;
Scene::~Scene() = default;

// ------------------------------------------------------------

Actor* Scene::NewActor()
{
    return _actors.Add(Ptr::NewUnique<Actor>(*this)).Get();
}

const List<UniquePtr<Actor>>& Scene::GetActors() const
{
    return _actors;
}

void Scene::Tick(EngineContext& context)
{
    for (auto& a : _actors)
    {
        a->Tick(context);
    }
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------