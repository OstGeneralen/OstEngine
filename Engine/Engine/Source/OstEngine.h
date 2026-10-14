// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Asset/AssetManager.h"
#include "Engine/EngineContext.h"
#include "Engine/Game/GameContext.h"
#include "Engine/Game/GameInterface.h"
#include "Engine/IOstEngine.h"
#include "Engine/System/InputReader.h"
#include "OstEngineContext.h"
#include "World/GameWorld.h"

#include <OstTypes.h>

#include <GraphicsEngine/Rendering/IRenderer.h>
#include <Memory/UniquePtr.h>
#include <Utility/Timer.h>

// ------------------------------------------------------------

namespace ost
{
    class IGraphicsResourceManager;
    class IMaterialManager;

    class OstEngine;

    class OstGameContext : public GameContext
    {
    public:
        OstGameContext(OstEngine& instance);

        UniquePtr<Scene> CreateScene(bool makeActive) override;
        void SetActiveScene(Scene& scene) override;

    private:
        OstEngine& _engineInstance;
    };

    class OstEngine : public IOstEngine
    {
        friend OstEngineContext;
        friend OstGameContext;

    public:
        OstEngine();
        ~OstEngine();

        void Initialize(UniquePtr<IGame>&& gameInstance, const OstEngineSettings& settings);

    public: // IOstEngine
        void Tick() override;
        void RenderSceneGraph(IRenderQueue& toQueue, const IRenderer& targetRenderer) override;

        InputReader& GetInputReader();

    private:
        Timer _timer;
        GameWorld _gameWorld;
        InputReader _input;
        AssetManager _assetManager;

        OstEngineContext _engineContext;
        OstGameContext _gameContext;

        UniquePtr<IGame> _gameInstance;
        Scene* _pActiveScene;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------