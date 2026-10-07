// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/GraphicsEngineSettings.h"
#include "GraphicsEngine/Objects/Buffer.h"
#include "GraphicsEngine/Objects/ObjectHandles.h"
#include "GraphicsEngine/Objects/PipelineStateObject.h"
#include "GraphicsEngine/Objects/Texture.h"
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

    class GraphicsEngine
    {
    public:
        GraphicsEngine();
        ~GraphicsEngine();

        void Initialize(const GraphicsEngineSettings& settings);
        void Shutdown();

        void UpdateSettings(const GraphicsEngineSettings& newSettings);

        
        void PushRenderCommand(const ModelHandle& model, const Matrix4x4& transform);
        void ExecuteRenderCommands(const Matrix4x4& view);
        void ClearRenderCommands();  

        IGraphicsResourceManager& GetResourceManager();

    private:
        GraphicsEngineSettings _activeSettings;
        UniquePtr<RenderHardwareInterface> _rhi;
        UniquePtr<GraphicsResourceManager> _resourceManager;

        List<RenderCommand> _commands;

        PipelineStateObject _defaultPSO;

        Buffer _frameBuffer;
        Buffer _objectBuffer;

        Texture _backbufferTexture;
        Texture _depthStencilTexture;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------