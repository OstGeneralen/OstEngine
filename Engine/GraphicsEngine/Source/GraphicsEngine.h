// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/IGraphicsEngine.h"

// Resources
#include "Objects/Texture.h"
#include "Objects/Buffer.h"
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
        GraphicsEngine();
        ~GraphicsEngine();

        bool IsInitialized() const;

        void Initialize(const GraphicsEngineSettings& settings);
        void Shutdown();

        // BEGIN IGraphicsEngine
        virtual void UpdateSettings(const GraphicsEngineSettings& settings) override;

        virtual IRenderer& GetRenderer() override;
        virtual IRenderQueue& GetRenderQueue() override;
        virtual IGraphicsResourceManager& GetResourceManager() override;
        virtual IMaterialManager& GetMaterialManager() override;

        void ExecuteAndClearCommandQueue() override;
        void Present(ERenderOutputTexture presentOutputTexture) override;

        const IRenderHardwareInterface& GetRenderHardwareInterface() const override;
        // END IGraphicsEngine

    private:
        RendererContext BuildRendererContext();

        Vector2f GetRenderSize() const;

        void UpdateFrameBuffer();
        void UpdateLightBuffer();

        Texture _backbuffer;
        Buffer _frameBuffer;
        Buffer _lightBuffer;
        Buffer _objectBuffer;
        Mesh _blitMesh;

        GraphicsEngineSettings _activeSettings;
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