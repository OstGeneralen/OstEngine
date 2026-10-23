// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GUI/Window/GUIWindow.h"

// ------------------------------------------------------------

namespace ost
{
    class AboutWindow : public GUIWindow
    {
    public:
        void DrawGUI(EditorContext& context) override;

        void OnOpen(EditorContext& context) override;
        void OnClose(EditorContext& context) override;

    private:
        bool _isOpen = false;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------