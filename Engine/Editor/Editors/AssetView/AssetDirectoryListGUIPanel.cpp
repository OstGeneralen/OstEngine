// Kasper "OstGeneralen" Esbjornsson - 2026
#include "AssetDirectoryListGUIPanel.h"

#include "EditorContext.h"
#include "GUI/IconsFontAwesome6.h"

using namespace ost;

// ------------------------------------------------------------

void ost::AssetDirectoryListGUIPanel::DrawGUI(EditorContext& context)
{
    OstGui::PushStyleColor(ImGuiCol_HeaderHovered, {1, 1, 1, 0.05f});
    OstGui::PushStyleColor(ImGuiCol_HeaderActive, {1, 1, 1, 0.1f});
    DrawDirectoryTreeRecursive(context, context.assetContext.GetRootAssetDirectory());
    OstGui::PopStyleColor(2);
}

void ost::AssetDirectoryListGUIPanel::DrawDirectoryTreeRecursive(EditorContext& context, AssetDirectoryEntry& forDirectoryEntry)
{
    const std::string idStr = forDirectoryEntry.path.string();
    const std::string nameStr = forDirectoryEntry.path.stem().string();

    Color textColor = Colors::White;
    textColor.A = context.assetContext.IsCurrentDirectoryEntry(forDirectoryEntry) ? 1.0f : 0.7f;

    ImGuiTreeNodeFlags nodeFlags = ImGuiTreeNodeFlags_OpenOnArrow;
    if (forDirectoryEntry.childEntries.IsEmpty())
    {
        nodeFlags |= ImGuiTreeNodeFlags_Leaf;
    }

    OstGui::PushStyleColor(ImGuiCol_Text, textColor);

    bool nodeOpen = OstGui::TreeNodeEx(idStr.c_str(), nodeFlags, "%s %s", ICON_FA_FOLDER, nameStr.c_str());
    if (OstGui::IsItemHovered())
    {
        if (OstGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
        {
            context.assetContext.SetCurrentAssetDirectory(forDirectoryEntry);
        }
    }

    if (nodeOpen)
    {

        for (auto& childEntry : forDirectoryEntry.childEntries)
        {
            DrawDirectoryTreeRecursive(context, childEntry);
        }

        OstGui::TreePop();
    }

    OstGui::PopStyleColor();
}

ImGuiChildFlags ost::AssetDirectoryListGUIPanel::GetDrawFlags() const
{
    return ImGuiChildFlags_Borders;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------