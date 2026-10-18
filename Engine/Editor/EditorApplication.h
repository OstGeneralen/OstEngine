// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <Engine/IOstEngine.h>
#include <Engine/Platform/Window.h>
#include <GraphicsEngine/IGraphicsEngine.h>
#include "EditorGameInstance.h"

// ------------------------------------------------------------

namespace ost
{
    class EditorApplication : IWindowHost
    {
    public:
        void Start();
        void Run();
        void Shutdown();

        // BEGIN IWindowHost
        void RequestExit() override;
        void Resized() override;
        void ProcessKeyEvent(EKeyboard key, bool state) override;
        // END IWindowHost
    private:
        bool _hasExitRequest = false;
        Window _window;
        UniquePtr<IOstEngine> _coreEngine;
        UniquePtr<IGraphicsEngine> _graphicsEngine;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------