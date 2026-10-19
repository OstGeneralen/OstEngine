// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Views/ViewContent.h"
#include <imgui.h>

// ------------------------------------------------------------

namespace ost
{
    class SceneOutlinerView : public ViewContent
    {
    public:
        SceneOutlinerView()
            : ViewContent("Scene Outliner")
        {
        }

        void Present(const ViewRect& viewRect) override
        {
            ImGui::Text("Scene Info Here");
        }
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------