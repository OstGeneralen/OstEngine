// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Views/View.h"

#include <imgui.h>
#include <string>

// ------------------------------------------------------------

namespace ost
{
    class ActorEditorView : public View
    {
    public:
        ActorEditorView()
        {
        }

        void Present(const ViewRect& viewRect, PropertyEditorCollection& propertyEditor) override
        {
            BeginPresent("Actor", viewRect);
            propertyEditor.DisplayEditor("Name##Actor", name);
            ImGui::Separator();
            ImGui::Text("Transform");
            propertyEditor.DisplayEditor("Position##Actor", translation);
            propertyEditor.DisplayEditor("Rotation##Actor", rotation);
            propertyEditor.DisplayEditor("Scale##Actor", scale);
            EndPresent();
        }

    private:
        std::string name = "Example Actor";

        Vector3f translation;
        Vector3f rotation;
        Vector3f scale = {1, 1, 1};
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------