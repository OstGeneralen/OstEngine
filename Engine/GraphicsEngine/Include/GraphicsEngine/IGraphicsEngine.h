// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Rendering/IGraphicsScene.h"
#include "GraphicsEngine/Rendering/ISceneRenderer.h"

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

        virtual IGraphicsScene& BeginRenderFrame() = 0;
        virtual void EndRenderFrame() = 0;

        virtual void PresentFrame() = 0;
    };

} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------