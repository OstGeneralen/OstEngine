// Kasper "OstGeneralen" Esbjornsson - 2026
#include "GUIStackPanel.h"

using namespace ost;

// ------------------------------------------------------------

GUIStackPanel& GUIStackPanel::SetOrientation(EGuiLayoutOrientation orientation)
{
    GUIPanel::SetOrientation(orientation);
    return *this;
}

GUIStackPanel& ost::GUIStackPanel::Bordered()
{
    _bordered = true;
    return *this;
}

// ------------------------------------------------------------

void ost::GUIStackPanel::DrawGUI(EditorContext& context)
{
    // Stack panel draws nothing :)
    // Just a bunch of children which the layout deals with on the whole
}

// ------------------------------------------------------------

ImGuiChildFlags ost::GUIStackPanel::GetDrawFlags() const
{
    if (_bordered)
    {
        return ImGuiChildFlags_Borders;
    }
    return 0;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------