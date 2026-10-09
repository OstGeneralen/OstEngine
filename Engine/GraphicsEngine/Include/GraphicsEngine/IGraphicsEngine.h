// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Rendering/IRenderQueue.h"
#include "GraphicsEngine/Rendering/IRenderer.h"
#include "GraphicsEngine/Resources/IGraphicsResourceManager.h"

#include <Memory/UniquePtr.h>

// ------------------------------------------------------------

namespace ost
{
    class IGraphicsEngine;

    // ------------------------------------------------------------

    enum class ERendererType
    {
        Forward,
    };

    struct GraphicsEngineSettings
    {
        struct OutputSettings
        {
            void* nativeWindowHandle = nullptr; // The handle of the window (for Win32 this is your HWND)
            Vector2u clientSize = {1600, 900};  // The resolution in pixels of the target
            Vector2f renderSize = {1, 1};       // The percentage of the client resolution to render at
        } output;

        struct RenderSettings
        {
            ERendererType rendererType = ERendererType::Forward;
            Color clearColor = Colors::Black;
        } renderer;
    };

    // ------------------------------------------------------------

    class IGraphicsEngine
    {
    public:
        static UniquePtr<IGraphicsEngine> CreateNew(const GraphicsEngineSettings& settings);

    public:
        virtual ~IGraphicsEngine() = default;

        virtual void UpdateSettings(const GraphicsEngineSettings& settings) = 0;

        virtual IRenderer& GetRenderer() = 0;
        virtual IRenderQueue& GetRenderQueue() = 0;
        virtual IGraphicsResourceManager& GetResourceManager() = 0;
        
        virtual void ExecuteAndClearCommandQueue() = 0;
    };

} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------