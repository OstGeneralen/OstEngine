// Kasper "OstGeneralen" Esbjornsson - 2026
#include "EditorMasterGUI.h"

#include "GUI/Layout/GUIStackPanel.h"

// Actual Windows/Panels
#include "GUI/Controls/GUIAssetDirectoryView.h"
#include "GUI/Controls/GUIAssetView.h"
#include "GUI/Controls/GUIPropertyEditor.h"
#include "GUI/Controls/GUISceneOutliner.h"
#include "GUI/Controls/GUISceneView.h"

using namespace ost;

// ------------------------------------------------------------

void ost::EditorMasterGUI::Initialize()
{
    auto& root = _layout.SetRootPanel<GUIStackPanel>("GUIRoot").SetOrientation(EGuiLayoutOrientation::Vertical);
    auto& upper = _layout.AddPanel<GUIStackPanel>(root, "GUITop", {0, 0.75f}).SetOrientation(EGuiLayoutOrientation::Horizontal);
    auto& lower = _layout.AddPanel<GUIStackPanel>(root, "GUIBottom", {0, 0.25f}).SetOrientation(EGuiLayoutOrientation::Horizontal);

    _layout.AddPanel<GUISceneOutliner>(upper, "GUISceneOutliner", {0.125f, 0});
    _layout.AddPanel<GUISceneView>(upper, "GUISceneView", {0.75f, 0});
    _layout.AddPanel<GUIPropertyEditor>(upper, "GUIPropertyEditor", {0.125f, 0});

    _layout.AddPanel<GUIAssetDirectoryView>(lower, "GUIAssetDirView", {0.3f, 0});
    _layout.AddPanel<GUIAssetView>(lower, "GUIAssetView", {0.7f, 0});
}

void ost::EditorMasterGUI::PrewarmGUI(const Vector2f& displaySize, EditorContext& context)
{
    _layout.PreWarmGUI(displaySize, context);
}

void ost::EditorMasterGUI::DisplayGUI(const Vector2f& displaySize, EditorContext& context)
{
    _layout.DrawGUI(displaySize, context);
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------
