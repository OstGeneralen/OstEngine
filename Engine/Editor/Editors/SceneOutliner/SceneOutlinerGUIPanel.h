// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GUI/IGUIContextMenuOwner.h"
#include "GUI/Layout/GUIPanel.h"

#include <string>

// ------------------------------------------------------------

namespace ost
{
    class Actor;

    class SceneOutlinerPanel : public GUIPanel, public IGUIContextMenuOwner
    {
    public:
        void DrawGUI(EditorContext& context) override;

        // BEGIN IGUIContextMenuOwner
        void DrawContextMenuGUI(EditorContext& context) override;
        // END IGUIContextMenuOwner

    private:
        ImGuiChildFlags GetDrawFlags() const override;
        SizeType _hoveredActorIndex = SizeTypeNpos;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------