// Kasper "OstGeneralen" Esbjornsson - 2026
#include "EditorGameInstance.h"

#include "EditorContext.h"

#include <Engine/Game/GameContext.h>

// World
#include <Engine/World/Actor.h>
#include <Engine/World/Scene.h>

// ------------------------------------------------------------

void ost::EditorGameInstance::Load(GameContext& context)
{
    _editorScene = context.CreateScene();
}

void ost::EditorGameInstance::Unload(GameContext& context)
{
}

void ost::EditorGameInstance::Update(GameContext& context)
{
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------