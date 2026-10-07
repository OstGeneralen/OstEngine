// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/GraphicsEngineSettings.h"
#include "GraphicsEngine/Objects/Buffer.h"
#include "GraphicsEngine/Objects/ObjectHandles.h"
#include "GraphicsEngine/Objects/PipelineStateObject.h"
#include "GraphicsEngine/Objects/Texture.h"
#include "GraphicsEngine/Rendering/IRenderer.h"
#include "GraphicsEngine/Rendering/RenderCommand.h"
#include "GraphicsEngine/Resources/IGraphicsResourceManager.h"

#include <Math/Vector2.h>
#include <Memory/UniquePtr.h>
#include <Utility/Assert.h>

// ------------------------------------------------------------

namespace ost
{
    class RenderHardwareInterface;
    class GraphicsResourceManager;

    class GraphicsEngine : public IRenderer
    {
    public:
        GraphicsEngine();
        ~GraphicsEngine();

        bool IsInitialized() const;

        void Initialize(const GraphicsEngineSettings& settings);
        void Shutdown();

        void UpdateSettings(const GraphicsEngineSettings& newSettings);

        IGraphicsResourceManager& GetResourceManager();

    public: // IRenderer
        void PushRenderCommand(const ModelHandle& model, const Matrix4x4& transform) override;
        void PushLightCommand( const RenderLight& light ) override;
        void ExecuteRenderCommands(const Matrix4x4& view) override;
        void ClearRenderCommands() override;

        Vector2f GetRenderDimensions() const override;

    private:
        GraphicsEngineSettings _activeSettings;
        UniquePtr<RenderHardwareInterface> _rhi;
        UniquePtr<GraphicsResourceManager> _resourceManager;

        List<RenderCommand> _commands;
        List<RenderLight> _lightCommands;

        PipelineStateObject _defaultPSO;

        Buffer _frameBuffer;
        Buffer _objectBuffer;
        Buffer _lightBuffer;

        Texture _backbufferTexture;
        Texture _depthStencilTexture;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------