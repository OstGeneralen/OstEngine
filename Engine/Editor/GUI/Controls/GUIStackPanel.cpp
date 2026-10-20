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
    ImGui::BeginChild(GetUIDString().c_str(), size, ImGuiChildFlags_Borders);

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

    ImGui::EndChild();
}

bool GUIStackPanel::AllowResizeX() const
{
    return _orientation == EOrientation::Vertical;
}

bool GUIStackPanel::AllowResizeY() const
{
    return _orientation == EOrientation::Horizontal;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------