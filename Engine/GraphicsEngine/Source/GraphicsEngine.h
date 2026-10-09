// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/IGraphicsEngine.h"
#include "RHI/RenderHardwareInterface.h"
#include "Rendering/RenderQueue.h"
#include "Resources/GraphicsResourceManager.h"

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

    public: // IGraphicsEngine
        virtual void UpdateSettings(const GraphicsEngineSettings& settings) override;

        virtual IRenderer& GetRenderer() override;
        virtual IRenderQueue& GetRenderQueue() override;
        virtual IGraphicsResourceManager& GetResourceManager() override;

        void ExecuteAndClearCommandQueue() override;

    private:
        Vector2f GetRenderSize() const;

        GraphicsEngineSettings _activeSettings;
        UniquePtr<IRenderer> _activeRenderer;

        RenderHardwareInterface _rhi;
        GraphicsResourceManager _resourceManager;
        RenderQueue _renderQueue;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------