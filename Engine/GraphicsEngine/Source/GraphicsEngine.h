// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/IGraphicsEngine.h"

// Resources
#include "Objects/Texture.h"
#include "Resources/GraphicsResourceManager.h"

// Rendering
#include "Objects/TextureSampler.h"
#include "Rendering/RenderPipelineConstants.h"
#include "Rendering/RenderResourceLibrary.h"
#include "Rendering/GraphicsScene.h"
#include "Rendering/SceneRenderer.h"

// Shared/Common
#include <Container/Map.h>
#include <Math/Vector2.h>

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

        IGraphicsScene& BeginGraphicsScene() override;
        void LockGraphicsScene() override;

        void ExecuteAndClearCommandQueue() override;
        void ClearAndSetBackbuffer() override;
        void Present() override;
        // END IGraphicsEngine

    private:
        ServiceLocator& _serviceLocator;
        
        Vector2u _outputSize;
        Vector2u _renderSize;

        Texture _backbuffer;

        Map<ESamplerSlot, TextureSampler> _samplers;

        RenderHardwareInterface _rhi;
        GraphicsResourceManager _resourceManager;

        RenderResourceLibrary _globalResourceLibrary;

        GraphicsScene _graphicsScene;
        SceneRenderer _sceneRenderer;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------