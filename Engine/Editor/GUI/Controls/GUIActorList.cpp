// Kasper "OstGeneralen" Esbjornsson - 2026
#include "GUIActorList.h"

#include "EditorContext.h"

#include <imgui.h>

// World
#include <Engine/World/Actor.h>
#include <Engine/World/ISceneManager.h>
#include <Engine/World/Scene.h>

using namespace ost;

// ------------------------------------------------------------

GUIActorList::GUIActorList()
    : GUIControl("ACTORLIST")
{
}

void ost::GUIActorList::Display()
{
    auto& services = EditorContext::Get().serviceLocator;
    ISceneManager* pSceneManager = services.Get<ISceneManager>();
    if (pSceneManager == nullptr)
    {
        return;
    }

    const auto& actors = pSceneManager->GetActiveScene()->GetAllActors();

    BeginGUI();

    for (const auto& actor : actors)
    {
        ImGui::Text(actor->GetName().GetString().c_str());
    }

    EndGUI();
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------