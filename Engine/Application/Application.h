// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Platform/Platform.h"

#include <Engine/IOstEngine.h>
#include <Engine/System/InputReader.h>
#include <GraphicsEngine/IGraphicsEngine.h>
#include <Memory/UniquePtr.h>

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
        void ProcessKeyEvent(EKeyboard key, bool state);

        void Run();

    private:
        GraphicsEngineSettings _graphicsEngineSettings;
        UniquePtr<IGraphicsEngine> _graphicsEngine;
        UniquePtr<IOstEngine> _coreEngine;

        platform::NativeWindow _window = nullptr;

        bool _hasExitRequest = false;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------