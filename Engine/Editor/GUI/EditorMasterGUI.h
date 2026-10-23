// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GUI/Layout/GUILayout.h"

#include <Math/Vector2.h>

// ------------------------------------------------------------

namespace ost
{
    class EditorMasterGUI
    {
    public:
        void Initialize();
        void PrewarmGUI(const Vector2f& displaySize, EditorContext& context);
        void DisplayGUI(const Vector2f& displaySize, EditorContext& context);

    private:
        GUILayout _layout;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------