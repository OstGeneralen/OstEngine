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

    class ForwardRenderer : public IRenderer
    {
    public:
        void Initialize(const Vector2f& renderSize, RenderHardwareInterface& rhi);

    public: // IRenderer
        void Resize(const Vector2f& newSize) override;

        Float32 GetAspectRatio() const override;
        const Vector2f& GetDimensions() const override;

        void ExecuteCommands(const Matrix4x4& view, const IRenderQueue& queue) override;

    private:
        RenderHardwareInterface* _rhi;
        Vector2f _currentRenderSize;

        Texture _backbuffer;
        Texture _depthStencil;

        Buffer _objectBuffer;
        Buffer _frameBuffer;
        Buffer _sceneLightBuffer;

        PipelineStateObject _defaultPSO;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------