// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GUI/Layout/GUIPanel.h"

// ------------------------------------------------------------

namespace ost
{
    class SceneViewGUIPanel : public GUIPanel
    {
    public:
        void DrawGUI(EditorContext& context) override;

        ImGuiChildFlags GetDrawFlags() const override;

    private:
        Vector2u _cachedSize;
    
    };
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------