// Kasper "OstGeneralen" Esbjornsson - 2026
#include "AssetViewGUIPanel.h"

#include "EditorContext.h"

using namespace ost;

// ------------------------------------------------------------

ost::AssetViewGUIPanel::AssetViewGUIPanel()
    : _hoveredEntryIndex{SizeTypeNpos}
{
}
// ------------------------------------------------------------

void AssetViewGUIPanel::DrawGUI(EditorContext& context)
{
    SizeType hoveredIndex = _hoveredEntryIndex;
    _hoveredEntryIndex = SizeTypeNpos;

    const auto& fileEntries = context.assetContext.GetCurrentDirectoryEntries();

    for (SizeType i = 0; i < fileEntries.GetSize(); ++i)
    {
        DrawAssetEntryGui(context, fileEntries[i], i == hoveredIndex);

        if (OstGui::IsItemHovered())
        {
            _hoveredEntryIndex = i;
        }
    }
}

ImGuiChildFlags ost::AssetViewGUIPanel::GetDrawFlags() const
{
    return ImGuiChildFlags_Borders;
}

// ------------------------------------------------------------

void ost::AssetViewGUIPanel::DrawAssetEntryGui(EditorContext& ctx, const AssetFileEntry& entry, bool hovered)
{
    Color bgColor = Colors::White;
    bgColor.A = hovered ? 0.1f : 0.0f;

    OstGui::PushStyleColor(ImGuiCol_ChildBg, bgColor);

    OstGui::BeginChild(entry.canonicalPath.string().c_str(), {0, 0}, ImGuiChildFlags_AutoResizeY);

    const EditorAssetTypeUtility assetUtil(entry.assetFileType);
    if (assetUtil.CanDragDrop() && OstGui::BeginDragDropSource())
    {
        SizeType dummy = 64;
        OstGui::SetDragDropPayload(assetUtil.GetDragDropTypeID(), &dummy, sizeof(SizeType));
        OstGui::Text("%s %s", assetUtil.GetAssetIconFontID(), entry.name.c_str());
        OstGui::EndDragDropSource();
    }
    
    OstGui::Text("%s %s", assetUtil.GetAssetIconFontID(), entry.name.c_str());

    OstGui::EndChild();

    OstGui::PopStyleColor();
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------