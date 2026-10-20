// Kasper "OstGeneralen" Esbjornsson - 2026
#include "GUIAssetsView.h"

#include "Content/IconProvider.h"
#include "EditorContext.h"

#include <imgui.h>

using namespace ost;

// ------------------------------------------------------------

GUIAssetsView::GUIAssetsView(const std::string& uidStr)
    : GUIControl{uidStr}
    , _isCurrentDirectoryRoot{true}
    , _currentPath{std::filesystem::current_path()}
    , _currentDirectoryContent{}
{
    SwitchDirectory(_currentPath);
}

void ost::GUIAssetsView::Display()
{
    ImGui::PushStyleColor(ImGuiCol_ChildBg, {0.2f,0.2f,0.2f,1});
    BeginGUI();
    ImGui::PopStyleColor();
    
    const Uint32 numColumns = static_cast<Uint32>(ImGui::GetContentRegionAvail().x) / 120u;
    std::filesystem::path targetDirectory = _currentPath;

    Uint32 index = 0;

    if (!_isCurrentDirectoryRoot)
    {
        DrawImageIcon(EIcon::Up, "Parent");
        if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
        {
            targetDirectory = _currentPath.parent_path();
        }
        index++;
    }


    Uint32 cachedCol = 0;

    for (const auto& entry : _currentDirectoryContent)
    {
        Uint32 col = index / numColumns;

        if (entry.isDirectory)
        {
            DrawImageIcon(EIcon::Folder, entry.name);
            if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
            {
                targetDirectory = _currentPath / entry.name;
            }
        }
        else
        {
            DrawImageIcon(EIcon::File, entry.name);
        }

        if(col == cachedCol)
        {
            ImGui::SameLine();
        }
        cachedCol = col;
    }

    EndGUI();

    if(targetDirectory != _currentPath)
    {
        SwitchDirectory( targetDirectory );
    }
}

void ost::GUIAssetsView::DrawImageIcon(EIcon icon, const std::string& label)
{
    ImGui::BeginGroup();
    EditorContext::Get().serviceLocator.Get<IconProvider>()->DrawGUIIcon(icon, {64, 64});
    ImGui::Text(label.c_str());
    ImGui::EndGroup();
}

void ost::GUIAssetsView::SwitchDirectory(const std::filesystem::path& newPath)
{
    _currentPath = newPath;
    _isCurrentDirectoryRoot = _currentPath == std::filesystem::current_path();

    _currentDirectoryContent.Clear();

    for (auto it : std::filesystem::directory_iterator(_currentPath))
    {
        DirectoryEntry entry;
        entry.name = it.path().filename().string();
        entry.path = std::filesystem::weakly_canonical(it.path()).string();
        entry.isDirectory = std::filesystem::is_directory(entry.path);

        _currentDirectoryContent.Add(entry);
    }
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------