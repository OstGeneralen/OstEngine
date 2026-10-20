// Kasper "OstGeneralen" Esbjornsson - 2026
#include "GUIStackPanel.h"

#include <imgui.h>

using namespace ost;

// ------------------------------------------------------------

GUIStackPanel::GUIStackPanel(const std::string& uid, EOrientation orientation)
    : GUIControl{uid}
    , _orientation{orientation}
{
}

void GUIStackPanel::Display()
{
    BeginGUI();

    bool firstChild = true;
    for (auto pChild : GetChildren())
    {
        if (!firstChild && _orientation == EOrientation::Horizontal)
        {
            ImGui::SameLine();
        }
        pChild->Display();
        firstChild = false;
    }

    EndGUI();
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------