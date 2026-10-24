// Kasper "OstGeneralen" Esbjornsson - 2026
#include "SceneOutlinerGUIPanel.h"

#include "EditorContext.h"
#include "GUI/Controls/PropertyEditorDrawer.h"

// Engine Scene
#include <Engine/World/Actor.h>
#include <Engine/World/ISceneManager.h>
#include <Engine/World/Scene.h>

using namespace ost;

// ------------------------------------------------------------

constexpr static Color SceneOutlineCol_ActorNameDefault = Colors::White;
constexpr static Color SceneOutlineCol_ActorNameSelected = Colors::Cyan;

// ------------------------------------------------------------

void SceneOutlinerPanel::DrawGUI(EditorContext& context)
{
    bool mouseOnActor = false;

    const SizeType lastHoveredIndex = _hoveredActorIndex;
    _hoveredActorIndex = SizeTypeNpos;

    bool mouseOverItem = false;

    for (SizeType actorIndex = 0; actorIndex < context.sceneContext.GetNumActors(); ++actorIndex)
    {
        const bool selected = context.sceneContext.IsActorSelected(actorIndex);
        const bool renaming = selected && context.sceneContext.IsSelectedActorRenaming();
        const bool isHovered = lastHoveredIndex == actorIndex;
        mouseOverItem |= isHovered;

        if (renaming)
        {
            context.guiContext.propertyDrawer.Draw<std::string>("##Rename", context.sceneContext.GetActorRenameBuffer());

            if (OstGui::IsKeyReleased(ImGuiKey_Enter))
            {
                context.sceneContext.ApplyActorRename();
            }
            else if (OstGui::IsKeyReleased(ImGuiKey_Escape) || OstGui::IsLMBClickedOutsideItem())
            {
                context.sceneContext.CancelActorRename();
            }

            if(OstGui::IsItemHovered())
            {
                _hoveredActorIndex = actorIndex;
            }
        }
        else
        {
            Color textCol = SceneOutlineCol_ActorNameDefault;
            textCol = selected ? SceneOutlineCol_ActorNameSelected : textCol;
            if (!isHovered)
            {
                textCol.A = 0.7f;
            }

            OstGui::TextColored(textCol, context.sceneContext.GetActorName(actorIndex));

            if (OstGui::IsLMBClickedInsideItem() || OstGui::IsRMBClickedInsideItem())
            {
                context.sceneContext.SelectActor(actorIndex);
            }
            if (OstGui::IsItemHovered())
            {
                _hoveredActorIndex = actorIndex;

                if (OstGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
                {
                    context.sceneContext.StartRenameSelectedActor();
                }
            }
        }
    }

    if (OstGui::IsRMBClickedInsideWindow())
    {
        context.guiContext.OpenContextMenu(*this);
    }
}

void ost::SceneOutlinerPanel::DrawContextMenuGUI(EditorContext& context)
{
    if (ImGui::Button("Create New", {ImGui::GetContentRegionAvail().x, 0}))
    {
        context.sceneContext.CreateNewActor();
        context.guiContext.CloseContextMenu();
    }

    ImGui::BeginDisabled(context.sceneContext.HasSelectedActor() == false);

    if (ImGui::Button("Delete", {ImGui::GetContentRegionAvail().x, 0}))
    {
        context.sceneContext.DeleteSelectedActor();
        context.guiContext.CloseContextMenu();
    }
    ImGui::EndDisabled();
}

ImGuiChildFlags ost::SceneOutlinerPanel::GetDrawFlags() const
{
    return ImGuiChildFlags_Borders;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------