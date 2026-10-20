// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Content/IconProvider.h"
#include "GUI/GUIControl.h"

#include <filesystem>

#include <Container/List.h>

// ------------------------------------------------------------

namespace ost
{
    struct DirectoryEntry
    {
        bool isDirectory = false;
        std::string name = "";
        std::filesystem::path path;
    };

    class GUIAssetsView : public GUIControl
    {
    public:
        GUIAssetsView(const std::string& uidStr);

        void Display() override;

    private:
        void DrawImageIcon(EIcon icon, const std::string& label);

        void SwitchDirectory(const std::filesystem::path& newPath);

        bool _isCurrentDirectoryRoot = true;
        std::filesystem::path _currentPath;

        List<DirectoryEntry> _currentDirectoryContent;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------