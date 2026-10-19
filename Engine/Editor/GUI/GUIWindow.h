// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GUI/GUIControl.h"
#include <imgui.h>

// ------------------------------------------------------------

namespace ost
{
    enum class EGUIWindowType
    {
        Standard, // Dockable to another host
        Modal,
    };

    enum class EGUIWindowOpenPos
    {
        Center,
        Cursor,
    };

    class GUIWindow
    {
    public:
        virtual EGUIWindowType GetWindowType()
        {
            return EGUIWindowType::Standard;
        }
        virtual void Display() = 0;

    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------