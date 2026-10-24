// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GUI/Layout/GUIPanel.h"

// ------------------------------------------------------------

namespace ost
{
    class GUIPropertyEditor : public GUIPanel
    {
    public:
        void DrawGUI(EditorContext& context) override
        {
            ImGui::Text("Property Edit");
        }

    private:
        ImGuiChildFlags GetDrawFlags() const override
        {
            return ImGuiChildFlags_Borders;
        }
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------