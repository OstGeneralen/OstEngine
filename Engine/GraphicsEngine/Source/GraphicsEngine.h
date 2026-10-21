// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/IGraphicsEngine.h"

// Resources
#include "Objects/Buffer.h"
#include "Objects/Texture.h"
#include "Resources/GraphicsResourceManager.h"

// Rendering
#include "GraphicsEngine/Rendering/IRenderer.h"
#include "Objects/TextureSampler.h"
#include "RHI/RenderHardwareInterface.h"
#include "Rendering/RenderPipelineConstants.h"
#include "Rendering/RenderQueue.h"
#include "Rendering/RendererContext.h"

// Shared/Common
#include <Container/Map.h>
#include <Math/Vector2.h>
#include <Memory/UniquePtr.h>
#include <Utility/Assert.h>

// ------------------------------------------------------------

namespace ost
{
    class RenderHardwareInterface;

    class GraphicsEngine : public IGraphicsEngine
    {
    public:
        GraphicsEngine(ServiceLocator& serviceLocator, void* windowHandle, const Vector2u& outputSize);
        ~GraphicsEngine();

        bool IsInitialized() const;

        void Shutdown();

        // BEGIN IGraphicsEngine
        void SetRenderSize(const Vector2u& renderSize) override;
        void SetOutputSize(const Vector2u& outputSize) override;

        virtual IRenderer& GetRenderer() override;
        virtual IRenderQueue& GetRenderQueue() override;

        void ExecuteAndClearCommandQueue() override;
        void DrawRendererOutput(ERenderOutputTexture presentOutputTexture) override;
        void Present() override;
        // END IGraphicsEngine

    private:
        void InitializeGlobalResources();

        RendererContext BuildRendererContext();

        void UpdateFrameBuffer();

        ServiceLocator& _serviceLocator;

        Texture _backbuffer;
        Buffer _frameBuffer;
        Buffer _objectBuffer;
        Mesh _blitMesh;

        UniquePtr<IRenderer> _activeRenderer;

        Map<ESamplerSlot, TextureSampler> _samplers;

        RenderHardwareInterface _rhi;
        GraphicsResourceManager _resourceManager;
        RenderQueue _renderQueue;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------