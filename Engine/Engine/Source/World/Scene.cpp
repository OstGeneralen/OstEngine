// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Engine/World/Scene.h"
#include "Engine/World/Actor.h"

using namespace ost;

// ------------------------------------------------------------

Scene::Scene(WorldContext& worldContext)
    : _actors{}
    , _worldContext{worldContext}
{
}

Scene::~Scene() = default;

// ------------------------------------------------------------

Actor* Scene::CreateActor()
{
    return _actors.Add(Ptr::NewUnique<Actor>(_worldContext)).Get();
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------