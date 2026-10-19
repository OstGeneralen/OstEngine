// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Views/ViewContent.h"
#include <imgui.h>

// ------------------------------------------------------------

namespace ost
{
    class AssetsView : public ViewContent
    {
    public:
        AssetsView()
            : ViewContent("Assets")
        {
        }

        void Present(const ViewRect& viewRect) override
        {
            ImGui::Text("Asset list will go here");
        }
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------