// Kasper "OstGeneralen" Esbjornsson - 2026
#include "SceneEditorContext.h"

#include <Engine/World/Actor.h>
#include <Engine/World/Scene.h>

using namespace ost;

// ------------------------------------------------------------

bool ost::SceneEditorContext::HasTargetActor() const
{
    return _pTargetActor != nullptr;
}

Actor* SceneEditorContext::GetTargetActor()
{
    return _pTargetActor;
}

void SceneEditorContext::SetTargetActor(Actor* pActor)
{
    Actor* pPreviousTarget = _pTargetActor;
    _pTargetActor = pActor;

    if (pPreviousTarget != _pTargetActor)
    {
        targetActorChanged.Broadcast();
    }
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------