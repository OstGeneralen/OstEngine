// Kasper "OstGeneralen" Esbjornsson - 2026
#include "GUIPanel.h"

#include <imgui.h>

using namespace ost;

// ------------------------------------------------------------

GUIPanel::GUIPanel(const std::string& uidString)
    : GUIControl{uidString}
{
}

void ost::GUIPanel::Display()
{
    BeginGUI();

    for (auto pChild : GetChildren())
    {
        pChild->Display();
    }

    EndGUI();
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------