// Kasper "OstGeneralen" Esbjornsson - 2026
#include "GUILayout.h"

#include <imgui.h>

// ------------------------------------------------------------

ost::GUILayout::GUILayout()
{
    _leftDockerWidthNorm = 0.08f;
    _rightDockerWidthNorm = 0.1f;
    _bottomDockerHeightNorm = 0.25f;
}

void ost::GUILayout::Display(const Vector2f& fullSize)
{
    // 1. Calculate presentation rects
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

    ImGui::SetNextWindowPos({0, ImGui::GetItemRectSize().y});
    ImGui::SetNextWindowSize({fullSize.X, fullSize.Y - ImGui::GetItemRectSize().y});

    ImGui::PushStyleColor(ImGuiCol_WindowBg, {0, 0, 0, 1});
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0, 0});
    ImGui::Begin("OstEditor##Master", 0, ImGuiWindowFlags_NoDecoration );
    ImGui::PopStyleColor();
    ImGui::PopStyleVar(); // Window Padding

    const Float32 topY = ImGui::GetItemRectSize().y;
    const Float32 botY = fullSize.Y;
    const Float32 leftX = 0;
    const Float32 rightX = fullSize.X;

    const Float32 initialLeftSize = 0.2f * fullSize.X;
    const Float32 initialBotHeight = 0.2f * fullSize.Y;
    const Float32 initialLeftHeight = (botY - topY) - initialBotHeight;

    ImGui::BeginChild("TopPanel", {0, initialLeftHeight}, ImGuiChildFlags_ResizeY);

    ImGui::BeginChild("LeftPanel##GUILayout", {initialLeftSize, ImGui::GetContentRegionAvail().y}, ImGuiChildFlags_Borders | ImGuiChildFlags_ResizeX);
    ImGui::EndChild();

    ImGui::SameLine();

    ImGui::BeginChild("SceneView##GUILayout", ImGui::GetContentRegionAvail(), ImGuiChildFlags_Borders);
    _sceneView.Display();
    ImGui::EndChild();

    ImGui::EndChild();

    ImGui::BeginChild("BottomPanel##GUILayout", {ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y}, ImGuiChildFlags_Borders);
    ImGui::EndChild();

    ImGui::End();
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------