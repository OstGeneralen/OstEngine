// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <Memory/UniquePtr.h>
#include <Services/ServiceLocator.h>

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

    // ------------------------------------------------------------

    class IGraphicsEngine
    {
    public:
        static UniquePtr<IGraphicsEngine> Create(ServiceLocator& appServiceLocator, void* windowHandle, const Vector2u& outputSize);

    public:
        virtual ~IGraphicsEngine() = default;

        virtual void SetRenderSize(const Vector2u& renderSize) = 0;
        virtual void SetOutputSize(const Vector2u& outputSize) = 0;

        virtual IRenderer& GetRenderer() = 0;
        virtual IRenderQueue& GetRenderQueue() = 0;

        virtual void ExecuteAndClearCommandQueue() = 0;
        virtual void ClearAndSetBackbuffer() = 0;
        virtual void DrawRendererOutput(ERenderOutputTexture presentOutputTexture = ERenderOutputTexture::Output) = 0;
        virtual void Present() = 0;
    };

} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------