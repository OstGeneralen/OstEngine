// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GUI/Window/GUIWindow.h"

// ------------------------------------------------------------

namespace ost
{
    class AddComponentPromptWindow : public GUIWindow
    {
    public:
        void DrawGUI(EditorContext& context) override;

        EGuiWindowMode GetWindowMode() const override;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------