// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Panel/EditorPanel.h"

// ------------------------------------------------------------

namespace ost
{
    class AssetsPanel : public EditorPanel
    {
    public:
        AssetsPanel()
        {
            _docking = EPanelDock::Bottom;
            _panelSize = {1.0f, 0.25f};
        }

        void DrawPanel() override
        {
            ImGui::Text("This is some test text");
        }
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------