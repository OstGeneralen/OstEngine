// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Views/View.h"

#include <Engine/Platform/Window.h>
#include <Memory/UniquePtr.h>

// ------------------------------------------------------------

namespace ost
{
    class MainView
    {
    public:
        void SetRoot(UniquePtr<View>&& root);

        void Present(const Window& mainWindow);

    private:
        UniquePtr<View> _rootElement;
    };

} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------