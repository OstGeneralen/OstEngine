// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Rendering/IRenderer.h"
#include "Objects/Buffer.h"
#include "Objects/PipelineStateObject.h"
#include "Objects/Texture.h"

// ------------------------------------------------------------

namespace ost
{
    class RenderHardwareInterface;
    class GraphicsResourceManager;

    class ForwardRenderer : public IRenderer
    {
    public: // IRenderer
        void Initialize(const Vector2u& renderSize, RendererContext&& context) override;
        void Resize(const Vector2u& newSize, RendererContext&& context) override;

        Float32 GetAspectRatio() const override;
        const Vector2f& GetDimensions() const override;

        void ExecuteCommands(const IRenderQueue& queue, RendererContext&& context) override;

    private:
        Vector2f _currentRenderSize;

        Texture _depthStencil;

        Buffer _objectBuffer;
        Buffer _frameBuffer;
        Buffer _sceneLightBuffer;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------