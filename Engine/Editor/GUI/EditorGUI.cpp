// Kasper "OstGeneralen" Esbjornsson - 2026
#include "EditorGUI.h"

#include <imgui.h>

using namespace ost;

// ------------------------------------------------------------

GUIControl& ost::EditorGUI::SetRoot(UniquePtr<GUIControl>&& root)
{
    _rootControl = std::move(root);
    return *_rootControl;
}

GUIControl& EditorGUI::GetRoot()
{
    return *_rootControl;
}

// ------------------------------------------------------------

void ost::EditorGUI::Display(const Vector2f& displaySize)
{
    Float32 menuHeight;
    DisplayMainMenu(menuHeight);

    ImGui::PushStyleColor(ImGuiCol_WindowBg, {0, 0, 0, 1});
    ImGui::Begin("##EditorGUIPrimary", 0, ImGuiWindowFlags_NoDecoration);
    ImGui::PopStyleColor();
    _rootControl->Display();
    ImGui::End();
}

// ------------------------------------------------------------

void ost::EditorGUI::DisplayMainMenu(Float32& outHeight)
{
    ImGui::BeginMainMenuBar();
    if (ImGui::BeginMenu("File"))
    {
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Options"))
    {
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("View"))
    {
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("About"))
    {
        ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();

    outHeight = ImGui::GetItemRectSize().y;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------
