// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Platform/Platform.h"

#include <Engine/OstEngine.h>
#include <GraphicsEngine/GraphicsEngine.h>

// ------------------------------------------------------------

namespace ost
{

    class Application
    {
    public:
        Application() = default;
        ~Application() = default;

        void Startup();
        void Shutdown();

        void RequestExit();
        void BeginWindowResize();
        void ExitWindowResize();

        void Run();

    private:
        OstEngine _coreEngine;

        GraphicsEngineSettings _graphicsEngineSettings;
        GraphicsEngine _graphicsEngine;

        platform::NativeWindow _window = nullptr;
        
        bool _hasExitRequest = false;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------