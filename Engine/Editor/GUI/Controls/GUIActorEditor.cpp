// Kasper "OstGeneralen" Esbjornsson - 2026
#include "GUIActorEditor.h"

// Engine
#include <Engine/IOstEngine.h>

// System
#include "GUI/PropertyEditor/PropertyEditorDrawer.h"
#include "System/SceneEditorContext.h"

// World
#include <Engine/World/Actor.h>
#include <Engine/World/Component.h>
#include <Engine/World/IComponentFactory.h>

// GUI
#include <imgui.h>

using namespace ost;

// ------------------------------------------------------------

ost::GUIActorEditor::GUIActorEditor(SceneEditorContext& sceneEditCtx)
    : GUIControl{"OSTGUIActorEditor"}
    , _sceneEditorCtx{sceneEditCtx}
    , _componentFactory{pEngine->GetServiceLocator().GetRequired<IComponentFactory>()}
    , _propertyDrawer{pEngine->GetServiceLocator().GetRequired<PropertyEditorDrawer>()}
    , _allComponentTypes{_componentFactory.GetRegisteredTypesInfo()}
    , _cachedTarget{nullptr}
{
    _sceneEditorCtx.targetActorChanged.Bind<GUIActorEditor, &GUIActorEditor::NewTargetActor>(this);
}

// ------------------------------------------------------------

void ost::GUIActorEditor::Display()
{
    BeginGUI();

    if (_cachedTarget)
    {
        ImGui::Text("Actor");
        ImGui::BeginChild("##actorInfo", {0, 0}, ImGuiChildFlags_Borders | ImGuiChildFlags_AutoResizeY);
        DisplayActorInfo(*_cachedTarget);
        ImGui::EndChild();

        ImGui::Spacing();
        ImGui::Spacing();

        ImGui::Text("Components");
        ImGui::BeginChild("##actorComponents", {0, 0}, ImGuiChildFlags_Borders);
        DisplayActorComponents(*_cachedTarget);
        ImGui::EndChild();
    }
    else
    {
        ImGui::TextColored({1, 1, 1, 0.5f}, "No target");
    }

    EndGUI();
}

// ------------------------------------------------------------

void ost::GUIActorEditor::DisplayActorInfo(Actor& target)
{
    _propertyDrawer.Draw("Name", _cachedName);
    if (ImGui::Button("Reset"))
    {
        _cachedName = target.GetName().GetString();
    }
    ImGui::SameLine();
    if (ImGui::Button("Apply"))
    {
        target.SetName(_cachedName);
    }
    ImGui::Spacing();

    // Actor Transform
    ImGui::Text("Transform");
    ImGui::Separator();

    Vector3f position = target.transform.GetWorldPosition();

    ImGui::DragFloat3("Position", position.Arr, 0.1f);
    ImGui::DragFloat3("Rotation", _cachedEulers.Arr, 0.1f);

    target.transform.SetWorldPosition(position);
    target.transform.SetWorldRotation(Quaternion::FromEulersDegrees(_cachedEulers));
}

void ost::GUIActorEditor::DisplayActorComponents(Actor& target)
{
    for (auto& componentInfo : _sceneEditorCtx.GetTargetActorComponentsInfo())
    {
        const char* componentTypeName = _componentFactory.GetTypeName(componentInfo.componentTypeID).c_str();

        // Component child + header
        ImGui::Text(componentTypeName);
        ImGui::PushID(componentTypeName);
        ImGui::BeginChild("##drawer", {0, 0}, ImGuiChildFlags_Borders | ImGuiChildFlags_AutoResizeY);

        auto propertySet = componentInfo.pComponent->GeneratePropertySet();
        for (auto& p : propertySet)
        {
            _propertyDrawer.Draw(p.type, p.name.data(), p.pData);
        }

        ImGui::EndChild();
        ImGui::PopID();
    }

    if (ImGui::Button("Add Component", {ImGui::GetContentRegionAvail().x, 0}))
    {
        //_addComponentWindow.SetOpen(true);
        ImGui::OpenPopup("AddComponentView");
    }
    if (ImGui::BeginPopup("AddComponentView", 0))
    {
        TypeID selectedType;
        if (DisplayComponentSelectPopup(target, selectedType))
        {
            target.AddComponent(selectedType);
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}

bool ost::GUIActorEditor::DisplayComponentSelectPopup(Actor& target, TypeID& selectedID)
{
    bool hasSelection = false;

    ImGui::Text("Add Component");

    ImGui::BeginChild("##AddComponentComponentList", {100, 200}, ImGuiChildFlags_Borders);
    for (const auto& c : _allComponentTypes)
    {
        if (target.GetComponent(c.typeId))
        {
            continue;
        }

        if (ImGui::Button(c.typeName.c_str(), {ImGui::GetContentRegionAvail().x, 0}))
        {
            hasSelection = true;
            selectedID = c.typeId;
        }
    }
    ImGui::EndChild();

    return hasSelection;
    return false;
}

// ------------------------------------------------------------

void GUIActorEditor::NewTargetActor()
{
    _cachedTarget = _sceneEditorCtx.GetTargetActor();
    if (_cachedTarget)
    {
        _cachedEulers = _sceneEditorCtx.GetTargetActor()->transform.GetWorldRotation().ToEulersDegrees();
        _cachedName = _sceneEditorCtx.GetTargetActor()->GetName().GetString();
    }
    else
    {
        _cachedEulers = {};
        _cachedName = "";
    }
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------