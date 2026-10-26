// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Editors/AssetView/Context/EditorAssetContext.h"
#include "GUI/Layout/GUIPanel.h"

#include <filesystem>

// ------------------------------------------------------------

namespace ost
{
    class AssetDirectoryListGUIPanel : public GUIPanel
    {
    public:
        void DrawGUI(EditorContext& context) override;

        ImGuiChildFlags GetDrawFlags() const override;

    private:
        void DrawDirectoryTreeRecursive(EditorContext& context, AssetDirectoryEntry& forDirectoryEntry);
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------