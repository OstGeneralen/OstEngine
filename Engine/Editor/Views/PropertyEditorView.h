// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Views/View.h"

#include <imgui.h>

// ------------------------------------------------------------

namespace ost
{
    class PropertyEditorView : public View
    {
    public:
        PropertyEditorView()
        {
        }

        void Present(const ViewRect& viewRect, PropertyEditorCollection& propertyEditor) override
        {
            BeginPresent("Properties", viewRect);
            ImGui::Text("This is where you'll edit components");
            EndPresent();
        }
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------