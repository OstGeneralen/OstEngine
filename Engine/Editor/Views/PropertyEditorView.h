// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Views/ViewContent.h"

#include <imgui.h>

// ------------------------------------------------------------

namespace ost
{
    class PropertyEditorView : public ViewContent
    {
    public:
        PropertyEditorView()
            : ViewContent("Property Editor")
        {
        }

        void Present(const ViewRect& viewRect) override
        {
            ImGui::Text("This is where you'll edit components");
        }
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------