// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once

#include <Engine/IOstEngine.h>
#include <Engine/Platform/Window.h>
#include <Engine/System/InputReader.h>
#include <GraphicsEngine/IGraphicsEngine.h>
#include <Memory/UniquePtr.h>

// ------------------------------------------------------------

namespace ost
{

    class Application : IWindowHost
    {
    public:
        Application() = default;
        ~Application() = default;

        void Startup();
        void Shutdown();

        void RequestExit() override;
        void Resized() override;
        void ProcessKeyEvent(EKeyboard key, bool state) override;

        void Run();

    private:
        GraphicsEngineSettings _graphicsEngineSettings;
        UniquePtr<IGraphicsEngine> _graphicsEngine;
        UniquePtr<IOstEngine> _coreEngine;

        Window _window;

        bool _hasExitRequest = false;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------