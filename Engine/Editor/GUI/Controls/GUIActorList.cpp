// Kasper "OstGeneralen" Esbjornsson - 2026
#include "GUIActorList.h"

#include "EditorContext.h"

#include <imgui.h>

// Editor
#include "System/SceneEditorContext.h"

// World
#include <Engine/World/Actor.h>
#include <Engine/World/ISceneManager.h>
#include <Engine/World/Scene.h>

using namespace ost;

// ------------------------------------------------------------

GUIActorList::GUIActorList(SceneEditorContext& sceneEditorCtx)
    : GUIControl("ACTORLIST")
    , _sceneEditorCtx{sceneEditorCtx}
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

    auto& actors = pSceneManager->GetActiveScene()->GetAllActors();

    BeginGUI();

    Actor* pSelected = _pCurrentSelectedActor;
    Actor* pHovered = _pCurrentHoveredActor;
    _pCurrentHoveredActor = nullptr;

    for (auto& actor : actors)
    {
        Actor* pActor = actor.Get();
        DisplayActor(*actor, pHovered == pActor, pSelected == pActor);
    }

    EndGUI();

    _sceneEditorCtx.SetTargetActor(_pCurrentSelectedActor);
}

// ------------------------------------------------------------

void ost::GUIActorList::DisplayActor(Actor& actor, bool hovered, bool selected)
{
    Actor* pActor = &actor;

    if (selected && hovered)
    {
        ImGui::PushStyleColor(ImGuiCol_Text, {1, 1, 0, 0.7f});
    }
    else if (selected)
    {
        ImGui::PushStyleColor(ImGuiCol_Text, {1, 1, 0, 1.0f});
    }
    else if (hovered)
    {
        ImGui::PushStyleColor(ImGuiCol_Text, {1, 1, 1, 0.7f});
    }
    else
    {
        ImGui::PushStyleColor(ImGuiCol_Text, {1, 1, 1, 1.0f});
    }

    ImGui::Text(actor.GetName().GetString().c_str());

    ImGui::PopStyleColor();

    if (ImGui::IsItemHovered())
    {
        _pCurrentHoveredActor = pActor;
        if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
        {
            _pCurrentSelectedActor = pActor;
        }
    }
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------