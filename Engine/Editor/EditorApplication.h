// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "EditorGameInstance.h"
#include "GUI/EditorGUI.h"

#include <Engine/IOstEngine.h>
#include <Engine/Platform/Window.h>
#include <GraphicsEngine/IGraphicsEngine.h>

// ------------------------------------------------------------

namespace ost
{
    class EditorApplication : IWindowHost
    {
    public:
        EditorApplication();
        ~EditorApplication();

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
        EditorGUI _editorGui;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------