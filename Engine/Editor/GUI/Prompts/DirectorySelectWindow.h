// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GUI/Window/GUIWindow.h"

#include <filesystem>

#include <Container/List.h>

// ------------------------------------------------------------

namespace ost
{
    class DirectorySelectWindow : public GUIWindow
    {
    public:
        DirectorySelectWindow();

        // BEGIN GUIWindow
        void DrawGUI(EditorContext& context) override;

        EGuiWindowMode GetWindowMode() const override;

        void OnOpen(EditorContext& context) override;
        // END GUIWindow

        bool HasSelection() const;

    private:
        void SwitchDirectory( std::filesystem::path toPath );

        struct Entry
        {
            std::string text;
            std::filesystem::path repPath;
        };

        List<Entry> _currentDirectoryEntries;
        SizeType _hoveredEntry = SizeTypeNpos;

        std::filesystem::path _currentPath;
        bool _hasSelection;
        std::filesystem::path _selectedPath;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------