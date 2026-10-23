// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "EditorContext.h"
#include "EditorGameInstance.h"
#include "GUI/EditorMasterGUI.h"
#include "SceneView/SceneViewCamera.h"

#include <Engine/IOstEngine.h>
#include <Engine/Platform/Window.h>
#include <GraphicsEngine/IGraphicsEngine.h>
#include <Services/ServiceLocator.h>

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
        ServiceLocator _serviceLocator;
        EditorContext _context;
        EditorGameInstance _editorGameInstance;
        UniquePtr<IOstEngine> _coreEngine;
        UniquePtr<IGraphicsEngine> _graphicsEngine;

        SceneViewCamera _sceneViewCamera;

        EditorMasterGUI _editorGui;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------