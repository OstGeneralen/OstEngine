// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <Math/Vector2.h>

// ------------------------------------------------------------

// clang-format off
#define GUI_WINDOW_OPTIONAL_RETURNVAL(rv) { return rv ; }
#define GUI_WINDOW_OPTIONAL_VOID { return; }
// clang-format on

// ------------------------------------------------------------

namespace ost
{
    struct EditorContext;

    enum class EGuiWindowMode
    {
        Default, // Allow interaction with the panel layout
        Modal,   // Block interaction with the panel layout
    };

    class GUIWindow
    {
    public:
        virtual ~GUIWindow() = default;

        virtual void DrawGUI(EditorContext& context) = 0;

        // Optional: Invoked when opened/closed respectively
        virtual void OnOpen(EditorContext& context) GUI_WINDOW_OPTIONAL_VOID;
        virtual void OnClose(EditorContext& context) GUI_WINDOW_OPTIONAL_VOID;

        // Optional: Allows windows to mark themselves as specific types
        virtual EGuiWindowMode GetWindowMode() const GUI_WINDOW_OPTIONAL_RETURNVAL(EGuiWindowMode::Default);
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------