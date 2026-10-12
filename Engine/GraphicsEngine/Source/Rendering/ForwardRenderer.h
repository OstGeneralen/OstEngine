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
    public:
        void Initialize(const Vector2f& renderSize, RenderHardwareInterface& rhi, GraphicsResourceManager& resources);

    public: // IRenderer
        void Resize(const Vector2f& newSize) override;

        Float32 GetAspectRatio() const override;
        const Vector2f& GetDimensions() const override;

        void ExecuteCommands(const RenderView& view, const IRenderQueue& queue) override;

    private:
        RenderHardwareInterface* _rhi;
        GraphicsResourceManager* _resources;

        Vector2f _currentRenderSize;

        Texture _backbuffer;
        Texture _depthStencil;

        Buffer _objectBuffer;
        Buffer _frameBuffer;
        Buffer _sceneLightBuffer;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------