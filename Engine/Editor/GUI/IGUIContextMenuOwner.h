// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once

// ------------------------------------------------------------

namespace ost
{
    struct EditorContext;

    class IGUIContextMenuOwner
    {
    public:
        virtual void DrawContextMenuGUI(EditorContext& context) = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------