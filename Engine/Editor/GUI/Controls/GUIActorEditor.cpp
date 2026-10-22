// Kasper "OstGeneralen" Esbjornsson - 2026
#include "GUIActorEditor.h"

// System
#include "System/SceneEditorContext.h"

// World
#include <Engine/World/Actor.h>
#include <Engine/World/Component.h>

// GUI
#include <imgui.h>

using namespace ost;

// ------------------------------------------------------------

ost::GUIActorEditor::GUIActorEditor(SceneEditorContext& sceneEditCtx)
    : GUIControl{"OSTGUIActorEditor"}
    , _sceneEditorCtx{sceneEditCtx}
{
}

// ------------------------------------------------------------

void ost::GUIActorEditor::Display()
{
    BeginGUI();

    if (_sceneEditorCtx.HasTargetActor() == false)
    {
        ImGui::TextColored({1, 1, 1, 0.5f}, "No current selected actor");
    }
    else
    {
        Vector3f position = _sceneEditorCtx.GetTargetActor()->transform.GetWorldPosition();
        Quaternion rotation = _sceneEditorCtx.GetTargetActor()->transform.GetWorldRotation();

        ImGui::DragFloat3("Position", position.Arr, 0.1f);
        ImGui::DragFloat3("Rotation", rotation.Arr, 0.1f);

        _sceneEditorCtx.GetTargetActor()->transform.SetWorldPosition(position);
        _sceneEditorCtx.GetTargetActor()->transform.SetWorldRotation(rotation);
    }

    EndGUI();
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------