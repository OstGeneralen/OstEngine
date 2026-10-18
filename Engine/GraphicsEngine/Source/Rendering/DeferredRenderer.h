// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Rendering/IRenderer.h"
#include "Objects/Buffer.h"
#include "Objects/Texture.h"
#include "Objects/Model.h"
#include "Objects/PipelineStateObject.h"

// ------------------------------------------------------------

namespace ost
{
    class RenderHardwareInterface;
    class GraphicsResourceManager;

    struct GBuffer
    {
        GBuffer();
        GBuffer(const GBuffer&);
        ~GBuffer();

        Texture albedo;
        Texture normals;
        Texture orm;
        Texture depth;
    };

    class DeferredRenderer : public IRenderer
    {
    public:
        DeferredRenderer();
        ~DeferredRenderer();

        // BEGIN IRenderer
        void Initialize(const Vector2u& renderSize, RendererContext&& context) override;
        void Resize(const Vector2u& newSize, RendererContext&& context) override;

        Float32 GetAspectRatio() const override;
        const Vector2f& GetDimensions() const override;

        void ExecuteCommands(const IRenderQueue& queue, RendererContext&& context) override;
        const ITexture* GetOutputTarget(ERenderOutputTexture target) const override;
        // END IRenderer

    private:
        Vector2f _currentSize;

        GBuffer _gBuffer;
        Texture _outputTexture;

        Buffer _lightBuffer;

        PipelineStateObject _fullscreenPSO;

    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------