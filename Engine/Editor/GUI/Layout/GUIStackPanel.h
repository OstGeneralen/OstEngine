// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GUI/Layout/GUIPanel.h"

// ------------------------------------------------------------

namespace ost
{
    class GUIStackPanel : public GUIPanel
    {
    public:
        GUIStackPanel& SetOrientation(EGuiLayoutOrientation orientation);
        GUIStackPanel& Bordered();

        void DrawGUI(EditorContext& context) override;

        ImGuiChildFlags GetDrawFlags() const override;

    private:
        bool _bordered = false;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------