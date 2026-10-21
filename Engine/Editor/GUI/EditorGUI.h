// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GUI/GUIControl.h"

#include <Memory/UniquePtr.h>

// ------------------------------------------------------------

namespace ost
{
    class EditorGUI
    {
    public:
        GUIControl& SetRoot( UniquePtr<GUIControl>&& root );
        GUIControl& GetRoot();

        void Display(const Vector2f& displaySize);
        void PostDisplay(GUIControl* pFor = nullptr);

    private:
        void DisplayMainMenu(Float32& outHeight);

        UniquePtr<GUIControl> _rootControl;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------