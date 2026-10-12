// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/IGraphicsEngine.h"
#include "Objects/TextureSampler.h"
#include "RHI/RenderHardwareInterface.h"
#include "Rendering/RenderPipelineConstants.h"
#include "Rendering/RenderQueue.h"
#include "Resources/GraphicsResourceManager.h"

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

        const IRenderHardwareInterface& GetRenderHardwareInterface() const override;
        // END IGraphicsEngine

    private:
        Vector2f GetRenderSize() const;

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