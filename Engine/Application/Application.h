// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once

#include <Engine/IOstEngine.h>
#include <Engine/Platform/Window.h>
#include <Engine/System/InputReader.h>
#include <GraphicsEngine/IGraphicsEngine.h>
#include <Memory/UniquePtr.h>
#include <Services/ServiceLocator.h>
#include <Engine/Game/GameBase.h>

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
        ServiceLocator _serviceLocator;

        UniquePtr<IGraphicsEngine> _graphicsEngine;
        UniquePtr<IOstEngine> _coreEngine;
        UniquePtr<GameBase> _gameInstance;

        Window _window;

        bool _hasExitRequest = false;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------