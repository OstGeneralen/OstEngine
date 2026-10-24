// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <imgui.h>

// ------------------------------------------------------------

namespace OstGui
{
    // Alias ImGui to OstGui for convenience
    // NOTE: I DO NOT CLAIM MYSELF AS AN OWNER NOR AUTHOR OF THE POSTIVIELY BRILLIANT DEARIMGUI LIBRARY
    // I JUST WANT A CONSISTENT NAMESPACE FOR MY IM GUI FUNCTIONS
    using namespace ImGui;

    inline bool IsMouseHoveringWindow()
    {
        return ImGui::IsMouseHoveringRect(ImGui::GetWindowContentRegionMin(), ImGui::GetWindowContentRegionMax());
    }
}; // namespace OstGui

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------