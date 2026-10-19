// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Views/View.h"
#include <imgui.h>
#include "PropertyEditors/BasicTypeEditors.h"

// ------------------------------------------------------------

namespace ost
{
    class SceneOutlinerView : public View
    {
    public:
        SceneOutlinerView()
        {
        }

        void Present(const ViewRect& viewRect, PropertyEditorCollection& properties) override
        {
            BeginPresent("Scene", viewRect);
            ImGui::Text("Scene Info Here");
            properties.DisplayEditor("Text", text);
            properties.DisplayEditor("Color", color);
            properties.DisplayEditor("Pos", v3);
            EndPresent();
        }

    private:
        std::string text = "Some Text";
        Color color = Color(Colors::Red);
        Vector3f v3 = {1,0,0};
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------