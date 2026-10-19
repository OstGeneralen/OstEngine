// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Views/View.h"
#include <imgui.h>

// ------------------------------------------------------------

namespace ost
{
    class AssetsView : public View
    {
    public:
        AssetsView()
        {
        }

        void Present(const ViewRect& viewRect, PropertyEditorCollection& propertyEditor) override
        {
            BeginPresent("Assets", viewRect);
            ImGui::Text("Asset list will go here");
            EndPresent();
        }
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------