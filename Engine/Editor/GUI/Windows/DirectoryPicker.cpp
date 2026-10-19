// Kasper "OstGeneralen" Esbjornsson - 2026
#include "DirectoryPicker.h"

#include <imgui.h>

using namespace ost;

// ------------------------------------------------------------

ost::DirectoryPicker::DirectoryPicker()
    : _currentPath{std::filesystem::current_path()}
{
}

void ost::DirectoryPicker::Display()
{
    const bool isAtRoot = _currentPath == std::filesystem::current_path();

    const std::string currentDirectoryPath = std::filesystem::relative(std::filesystem::weakly_canonical(_currentPath)).string();

    ImGui::Begin("Directory Picker");

    // Display Path + Move Forwards
    ImGui::BeginDisabled(isAtRoot);
    if (ImGui::Button("<<##DirectoryPicker"))
    {
        _currentPath = _currentPath.parent_path();
    }
    ImGui::EndDisabled();

    ImGui::SameLine();

    ImGui::Text(currentDirectoryPath.c_str());

    // Display content of current directory

    std::filesystem::path newPath = _currentPath;

    ImGui::BeginChild("Content##DirectoryPicker", {0, 0}, ImGuiChildFlags_Borders);
    for (const auto& fs : std::filesystem::directory_iterator(_currentPath))
    {
        const std::string labelText = fs.path().filename().string();

        if (std::filesystem::is_directory(fs.path()))
        {
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4{1, 1, 1, 1});
        }
        else
        {
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4{0.5f, 0.5f, 0.5f, 1});
        }

        // This should be a clickable link
        ImGui::Text(labelText.c_str());

        if (std::filesystem::is_directory(fs.path()))
        {
            if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
            {
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1,0,0,1));
                ImGui::PopStyleColor();
                newPath = fs.path();
            }
        }

        ImGui::PopStyleColor();
    }

    _currentPath = newPath;

    ImGui::EndChild();

    ImGui::End();
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------