// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <imgui.h>
#include "IconsFontAwesome6.h"

// ------------------------------------------------------------

namespace OstGui
{
    // Alias ImGui to OstGui for convenience
    // NOTE: I DO NOT CLAIM MYSELF AS AN OWNER NOR AUTHOR OF THE POSTIVIELY BRILLIANT DEARIMGUI LIBRARY
    // I JUST WANT A CONSISTENT NAMESPACE FOR MY IM GUI FUNCTIONS
    using namespace ImGui;

    inline bool IsMouseHoveringWindow()
    {
        return IsMouseHoveringRect(GetWindowContentRegionMin(), GetWindowContentRegionMax());
    }

    inline bool IsLMBClickedInsideWindow()
    {
        return IsMouseHoveringWindow() && IsMouseClicked(ImGuiMouseButton_Left);
    }
    inline bool IsRMBClickedInsideWindow()
    {
        return IsMouseHoveringWindow() && IsMouseClicked(ImGuiMouseButton_Right);
    }

    inline bool IsLMBClickedOutsideWindow()
    {
        return !IsMouseHoveringWindow() && IsMouseClicked(ImGuiMouseButton_Left);
    }
    inline bool IsRMBClickedOutsideWindow()
    {
        return !IsMouseHoveringWindow() && IsMouseClicked(ImGuiMouseButton_Right);
    }

    inline bool IsLMBClickedInsideItem()
    {
        return IsItemHovered() && IsMouseClicked(ImGuiMouseButton_Left);
    }
    inline bool IsRMBClickedInsideItem()
    {
        return IsItemHovered() && IsMouseClicked(ImGuiMouseButton_Right);
    }

    inline bool IsLMBClickedOutsideItem()
    {
        return !IsItemHovered() && IsMouseClicked(ImGuiMouseButton_Left);
    }
    inline bool IsRMBClickedOutsideItem()
    {
        return !IsItemHovered() && IsMouseClicked(ImGuiMouseButton_Right);
    }

}; // namespace OstGui

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------