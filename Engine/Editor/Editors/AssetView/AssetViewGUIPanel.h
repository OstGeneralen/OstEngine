// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Editors/AssetView/AssetTypes.h"
#include "Editors/AssetView/Context/EditorAssetContext.h"
#include "GUI/Layout/GUIPanel.h"

#include <filesystem>

#include <Container/List.h>

// ------------------------------------------------------------

namespace ost
{
    class AssetViewGUIPanel : public GUIPanel
    {
    public:
        AssetViewGUIPanel();

        void DrawGUI(EditorContext& context) override;

        ImGuiChildFlags GetDrawFlags() const override;

    private:
        void DrawAssetEntryGui(EditorContext& ctx, const AssetFileEntry& entry, bool hovered);
        void ChangePath(const std::filesystem::path& toPath);

        SizeType _hoveredEntryIndex = SizeTypeNpos;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------