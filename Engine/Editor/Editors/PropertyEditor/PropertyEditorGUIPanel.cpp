// Kasper "OstGeneralen" Esbjornsson - 2026
#include "PropertyEditorGUIPanel.h"

#include "Commands/ComponentCommands.h"
#include "EditorContext.h"
#include "Windows/AddComponentPromptWindow.h"

#include <Engine/World/Actor.h>
#include <Engine/World/IComponentFactory.h>

using namespace ost;

// ------------------------------------------------------------

void PropertyEditorGUIPanel::DrawGUI(EditorContext& context)
{
    Actor* pActor = context.sceneContext.GetSelectedActorPtr();
    IComponentFactory& componentFactory = context.serviceLocator.GetRequired<IComponentFactory>();

    if (pActor == nullptr)
    {
        OstGui::TextColored({1, 1, 1, 0.6f}, "No Selected Actor");
        return;
    }

    // Update target if changed
    if (pActor != _pTarget)
    {
        _rotation = pActor->transform.GetRotation().ToEulersDegrees();
        _position = pActor->transform.GetPosition();
        _pTarget = pActor;
    }

    // Draw Tranform Field
    OstGui::BeginChild("Transform", {0, 0}, ImGuiChildFlags_AutoResizeY);
    OstGui::Text("Transform");
    context.guiContext.propertyDrawer.Draw<Vector3f>("Position", _position);
    context.guiContext.propertyDrawer.Draw<Vector3f>("Rotation", _rotation);
    OstGui::EndChild();

    OstGui::Separator();

    // Draw Component Fields
    OstGui::Text("Components");
    OstGui::BeginChild("##Components", {0, 0}, ImGuiChildFlags_AutoResizeY);
    for (auto& comp : context.sceneContext.GetSelectedActorComponents())
    {
        DrawComponentGui(context, comp.componentTypeID, componentFactory.GetTypeName(comp.componentTypeID).c_str(), comp.pComponent);
    }
    OstGui::EndChild();

    OstGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, {0.5f, 0.5f});
    if (OstGui::Button("Add New", {OstGui::GetContentRegionAvail().x, 0}))
    {
        context.guiContext.OpenWindow<AddComponentPromptWindow>();
    }
    OstGui::PopStyleVar();
}

ImGuiChildFlags ost::PropertyEditorGUIPanel::GetDrawFlags() const
{
    return 0;
}

void ost::PropertyEditorGUIPanel::DrawComponentGui(EditorContext& context, TypeID componentType, const char* componentName, ActorComponent* pComponent)
{
    OstGui::PushID(componentName);

    OstGui::PushStyleColor(ImGuiCol_ChildBg, {0.07f, 0.07f, 0.07f, 1.0f});
    OstGui::BeginChild("##Container", {0, 0}, ImGuiChildFlags_AutoResizeY | ImGuiChildFlags_Borders); // Container
    OstGui::PopStyleColor();

    { // Header

        const Float32 yOffset = OstGui::CalcTextSize(componentName).y / 4.0f;

        OstGui::SetCursorPosY(OstGui::GetCursorPosY() + yOffset);
        OstGui::Text(componentName);
        OstGui::SameLine();

        OstGui::SetCursorPosY(OstGui::GetCursorPosY() - yOffset);

        OstGui::SetCursorPosX(OstGui::GetCursorPosX() + OstGui::GetContentRegionAvail().x - OstGui::CalcTextSize("Delete").x - OstGui::GetStyle().ItemSpacing.x -
                              OstGui::GetStyle().ItemInnerSpacing.x);

        if (OstGui::Button("Delete"))
        {
            context.commandQueue.PushCommand(Ptr::NewUnique<RemoveComponentEditorCommand>(componentType));
        }
    }

    OstGui::Separator();

    { // Content
        OstGui::BeginChild(componentName, {0, 0}, ImGuiChildFlags_AutoResizeY);
        for (auto& prop : pComponent->GeneratePropertySet())
        {
            context.guiContext.propertyDrawer.Draw(prop.type, prop.name.data(), prop.pData);
        }
        OstGui::EndChild();
    }

    OstGui::EndChild(); // Container

    OstGui::PopID();
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------