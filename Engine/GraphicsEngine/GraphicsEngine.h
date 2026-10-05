// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/GraphicsEngineSettings.h"
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
        static GraphicsEngine& GetInstance();

    private:
        static GraphicsEngine* _pInstance;

    public:
        GraphicsEngine();
        ~GraphicsEngine();

        void Initialize(const GraphicsEngineSettings& settings);
        void Shutdown();

        void UpdateSettings(const GraphicsEngineSettings& newSettings);

        void Draw(const ModelHandle& model, const Matrix4x4& transform);

        void DoRender(bool maintainCommandList = false);

        IGraphicsResourceManager& GetResourceManager();

    private:
        GraphicsEngineSettings _activeSettings;
        UniquePtr<RenderHardwareInterface> _rhi;
        UniquePtr<GraphicsResourceManager> _resourceManager;

        List<RenderCommand> _commands;

        Texture _backbufferTexture;
        Texture _depthStencilTexture;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------