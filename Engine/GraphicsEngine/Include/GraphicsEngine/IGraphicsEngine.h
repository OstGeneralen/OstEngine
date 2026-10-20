// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/IRenderHardwareInterface.h"
#include "GraphicsEngine/Materials/IMaterialManager.h"
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
        Deferred,
    };

    struct GraphicsEngineSettings
    {
        struct OutputSettings
        {
            bool fullscreen = false;
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

        virtual void SetRenderSize(const Vector2u& renderSize) = 0;
        virtual void SetOutputSize(const Vector2u& outputSize) = 0;

        virtual IRenderer& GetRenderer() = 0;
        virtual IRenderQueue& GetRenderQueue() = 0;
        virtual IGraphicsResourceManager& GetResourceManager() = 0;
        virtual IMaterialManager& GetMaterialManager() = 0;

        virtual void ExecuteAndClearCommandQueue() = 0;
        virtual void DrawRendererOutput(ERenderOutputTexture presentOutputTexture = ERenderOutputTexture::Output) = 0;
        virtual void Present() = 0;

        virtual const IRenderHardwareInterface& GetRenderHardwareInterface() const = 0;
    };

} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------