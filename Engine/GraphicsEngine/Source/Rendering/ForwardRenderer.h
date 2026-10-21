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
        const ITexture* GetOutputTarget( ERenderOutputTexture outputTarget ) const override;

    private:
        Vector2f _currentRenderSize;

        Buffer _lightBuffer;

        Texture _color;
        Texture _depthStencil;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------