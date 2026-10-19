// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <imgui.h>

#include <Math/Vector2.h>
#include "PropertyEditors/PropertyEditorCollection.h"

// ------------------------------------------------------------

namespace ost
{
    struct ViewRect
    {
        Vector2f position;
        Vector2f size;
    };

    class View
    {
    public:
        virtual ~View() = default;
        virtual void Present(const ViewRect& viewRect, PropertyEditorCollection& propertyEditor) = 0;

    protected:
        void BeginPresent(const char* name, const ViewRect& viewRect)
        {
            ImGui::SetNextWindowPos(viewRect.position);
            ImGui::SetNextWindowSize(viewRect.size);
            ImGui::Begin(name, 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove);
        }
        void EndPresent()
        {
            ImGui::End();
        }
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------