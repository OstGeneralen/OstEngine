// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "EditorContext.h"

#include <imgui.h>

#include <Math/Vector2.h>

// ------------------------------------------------------------

namespace ost
{
    enum class EPanelDock
    {
        Floating,
        Left,
        Right,
        Top,
        Bottom,
    };

    class EditorPanel
    {
    public:
        virtual ~EditorPanel() = default;
        void Draw()
        {
            auto clientSize = EditorContext::Get().window.GetClientSize().VectorCast<Float32>();

            Vector2f size = {0, 0};
            size = {clientSize.X * _panelSize.X, clientSize.Y * _panelSize.Y};

            Vector2f pos = {0, 0};
            switch (_docking)
            {
            case EPanelDock::Bottom:
                pos = {0.0f, clientSize.Y - size.Y};
                break;
            case EPanelDock::Top:
                pos = {0.0f, 0};
                break;
            case EPanelDock::Left:
                pos = {0.0f, 0};
                break;
            case EPanelDock::Right:
                pos = {clientSize.X - size.X, 0};
                break;
            }

            ImGui::SetNextWindowPos(pos);
            ImGui::SetNextWindowSize(size);
            ImGui::Begin("Test", 0, ImGuiWindowFlags_NoDecoration);
            DrawPanel();
            ImGui::End();
        }

    protected:
        virtual void DrawPanel() = 0;

        Vector2f _panelSize;
        EPanelDock _docking = EPanelDock::Floating;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------