// Kasper "OstGeneralen" Esbjornsson - 2026
#include "SceneOutlinerGUIPanel.h"

#include "EditorContext.h"
#include "GUI/IEditorGUI.h"
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
    IEditorGUI& editorGui = context.serviceLocator.GetRequired<IEditorGUI>();
    PropertyEditorDrawer& propertyDrawer = context.serviceLocator.GetRequired<PropertyEditorDrawer>();

    const Scene* pActiveScene = context.serviceLocator.GetRequired<ISceneManager>().GetActiveScene();
    const auto& allActors = pActiveScene->GetAllActors();

    const Actor* pHoveredActor = _pCachedHoveredActor;
    _pCachedHoveredActor = nullptr;

    bool mouseOnActor = false;

    for (const auto& pActor : allActors)
    {
        if (_pCachedRenameActor == pActor.Get())
        {
            propertyDrawer.Draw<std::string>("##Rename", _cachedActorName);
            ImGui::SetKeyboardFocusHere(-1);

            if (ImGui::IsKeyReleased(ImGuiKey_Enter))
            {
                // Send rename actor command
                _pCachedRenameActor = nullptr;
            }
            else if (ImGui::IsKeyReleased(ImGuiKey_Escape) || ImGui::IsItemHovered() == false && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
            {
                // Dont rename actor
                _pCachedRenameActor = nullptr;
            }
        }
        else
        {
            Color textCol = SceneOutlineCol_ActorNameDefault;
            textCol = _pCachedSelectedActor == pActor.Get() ? SceneOutlineCol_ActorNameSelected : textCol;
            if (pHoveredActor != pActor.Get())
            {
                textCol.A = 0.7f;
            }

            OstGui::TextColored(textCol, pActor->GetName().GetString().c_str());

            if (OstGui::IsItemHovered())
            {
                _pCachedHoveredActor = pActor.Get();
                mouseOnActor = true;

                if (OstGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
                {
                    _pCachedRenameActor = pActor.Get();
                    _cachedActorName = pActor->GetName().GetString();
                }
            }
            if (OstGui::IsItemClicked(ImGuiMouseButton_Left) || OstGui::IsItemClicked(ImGuiMouseButton_Right))
            {
                _pCachedSelectedActor = pActor.Get();
            }
        }
    }

    if ((OstGui::IsMouseClicked(ImGuiMouseButton_Left) || OstGui::IsMouseClicked(ImGuiMouseButton_Right)) && !mouseOnActor && OstGui::IsWindowFocused())
    {
        _pCachedSelectedActor = nullptr;
    }

    if (OstGui::IsMouseHoveringWindow() && OstGui::IsMouseReleased(ImGuiMouseButton_Right) && OstGui::IsWindowFocused())
    {
        editorGui.OpenContextMenu(*this);
    }
}

void ost::SceneOutlinerPanel::DrawContextMenuGUI(EditorContext& context)
{
    if (ImGui::Button("Create New", {ImGui::GetContentRegionAvail().x, 0}))
    {
        // Todo: send create actor command
        context.serviceLocator.GetRequired<IEditorGUI>().CloseContextMenu();
    }

    ImGui::BeginDisabled(_pCachedSelectedActor == nullptr);

    if (ImGui::Button("Delete", {ImGui::GetContentRegionAvail().x, 0}))
    {
        // Todo: send delete actor commend
        context.serviceLocator.GetRequired<IEditorGUI>().CloseContextMenu();
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