// Kasper "OstGeneralen" Esbjornsson - 2026
#include "DirectorySelectWindow.h"

#include "EditorContext.h"

using namespace ost;

// ------------------------------------------------------------

ost::DirectorySelectWindow::DirectorySelectWindow()
    : _currentPath{std::filesystem::weakly_canonical(std::filesystem::current_path())}
{
}

void ost::DirectorySelectWindow::DrawGUI(EditorContext& context)
{
    bool open = true;
    std::filesystem::path newPath = _currentPath;
    SizeType hoveredEntry = _hoveredEntry;
    _hoveredEntry = SizeTypeNpos;

    OstGui::SetNextWindowPos(Vector2f(OstGui::GetMainViewport()->Size) * 0.5f, 0, {0.5f, 0.5f});

    OstGui::Begin("Directory Select##GUIPrompt", &open, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoScrollbar);

    OstGui::TextColored({1, 1, 1, 0.6f}, std::filesystem::relative(_currentPath).string().c_str());

    OstGui::BeginChild("##DirectoriesOutline", Vector2f(OstGui::GetMainViewport()->Size) * 0.3f, ImGuiChildFlags_Borders);

    for (SizeType i = 0; i < _currentDirectoryEntries.GetSize(); ++i)
    {
        Color drawCol = Colors::White;
        drawCol.A = i == hoveredEntry ? 1.0f : 0.8f;

        OstGui::TextColored(drawCol, _currentDirectoryEntries[i].text.c_str());

        if (OstGui::IsItemHovered())
        {
            _hoveredEntry = i;
            if (OstGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
            {
                newPath = _currentDirectoryEntries[i].repPath;
            }
        }
    }

    OstGui::EndChild();

    OstGui::SetCursorPosX(OstGui::GetCursorPosX() + OstGui::GetContentRegionAvail().x - OstGui::CalcTextSize("Select").x - OstGui::GetStyle().ItemSpacing.x -
                          OstGui::GetStyle().ItemInnerSpacing.x);
    if (OstGui::Button("Select"))
    {
        _selectedPath = std::filesystem::relative(_currentPath);
        _hasSelection = true;
        open = false;
    }

    OstGui::End();

    if (_currentPath != newPath)
    {
        SwitchDirectory(newPath);
    }

    if (!open)
    {
        context.guiContext.CloseWindow<DirectorySelectWindow>();
    }
}

EGuiWindowMode ost::DirectorySelectWindow::GetWindowMode() const
{
    return EGuiWindowMode::Modal;
}

void ost::DirectorySelectWindow::OnOpen(EditorContext& context)
{
    _hasSelection = false;
    SwitchDirectory(_currentPath);
}

// ------------------------------------------------------------

bool ost::DirectorySelectWindow::HasSelection() const
{
    return _hasSelection;
}

// ------------------------------------------------------------

void ost::DirectorySelectWindow::SwitchDirectory(std::filesystem::path toPath)
{
    _currentPath = toPath;

    _currentDirectoryEntries.Clear();

    if (_currentPath.has_parent_path())
    {
        Entry e;
        e.text = "..\\";
        e.repPath = std::filesystem::weakly_canonical(_currentPath.parent_path());
        _currentDirectoryEntries.Add(e);
    }

    for (auto it : std::filesystem::directory_iterator(_currentPath))
    {
        if (it.is_directory())
        {
            Entry e;
            e.repPath = std::filesystem::weakly_canonical(it.path());
            e.text = it.path().filename().string();
            _currentDirectoryEntries.Add(e);
        }
    }

    _hoveredEntry = SizeTypeNpos;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------