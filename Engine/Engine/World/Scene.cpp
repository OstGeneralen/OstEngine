// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Scene.h"
#include "Actor.h"

using namespace ost;

// ------------------------------------------------------------

Scene::Scene(WorldContext& worldContext)
    : _actors{}
    , _worldContext{worldContext}
{
}

// ------------------------------------------------------------

Actor* Scene::CreateActor()
{
    return _actors.Add(Ptr::NewUnique<Actor>(_worldContext)).Get();
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------