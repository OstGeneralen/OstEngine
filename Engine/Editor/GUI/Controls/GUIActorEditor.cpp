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
    _sceneEditorCtx.targetActorChanged.Bind<GUIActorEditor, &GUIActorEditor::NewTargetActor>(this);
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

        ImGui::DragFloat3("Position", position.Arr, 0.1f);
        ImGui::DragFloat3("Rotation", _cachedEulers.Arr, 0.1f);

        _sceneEditorCtx.GetTargetActor()->transform.SetWorldPosition(position);
        _sceneEditorCtx.GetTargetActor()->transform.SetWorldRotation(Quaternion::FromEulersDegrees(_cachedEulers));
    }

    EndGUI();
}

void GUIActorEditor::NewTargetActor()
{
    if(_sceneEditorCtx.HasTargetActor())
    {
        _cachedEulers = _sceneEditorCtx.GetTargetActor()->transform.GetWorldRotation().ToEulersDegrees();
    }
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------