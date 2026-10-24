// Kasper "OstGeneralen" Esbjornsson - 2026
#include "SceneViewGUIPanel.h"

#include "EditorContext.h"

using namespace ost;

// ------------------------------------------------------------

void SceneViewGUIPanel::DrawGUI(EditorContext& context)
{
    const Vector2f size = OstGui::GetContentRegionAvail();

    OstGui::Image(context.sceneViewContext.GetSceneViewOutput(), size);
    context.sceneViewContext.SetOutputSize(size);
}

ImGuiChildFlags ost::SceneViewGUIPanel::GetDrawFlags() const
{
    return ImGuiChildFlags_Borders;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------