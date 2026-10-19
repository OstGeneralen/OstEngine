// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GUI/GUIWindow.h"
#include <filesystem>

// ------------------------------------------------------------

namespace ost
{
    class DirectoryPicker : public GUIWindow
    {
    public:
        DirectoryPicker();
        void Display() override;

    private:
        std::filesystem::path _currentPath;
    };
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------