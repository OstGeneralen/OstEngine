// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Asset/AssetManager.h"
#include "Engine/EngineContext.h"
#include "Engine/Game/GameInterface.h"
#include "Engine/IOstEngine.h"
#include "Engine/System/InputReader.h"
#include "World/GameWorld.h"

#include <OstTypes.h>

#include <GraphicsEngine/Rendering/IRenderer.h>
#include <Memory/UniquePtr.h>
#include <Utility/Timer.h>

// ------------------------------------------------------------

namespace ost
{
    class IGraphicsResourceManager;

    class OstEngine;

    class OstEngineContext : public EngineContext
    {
    public:
        OstEngineContext(OstEngine& instance);

    public: // EngineContext
        IAssetManager& Assets() override;
        const TimeStructure& Time() const override;
        const InputReader& GetInput() const;

        UniquePtr<Scene> CreateScene(bool makeActive) override;
        void SetActiveScene(Scene& scene) override;

    private:
        OstEngine& _engineInstance;
    };

    class OstEngine : public IOstEngine
    {
        friend OstEngineContext;

    public:
        OstEngine();
        ~OstEngine();

        void Initialize(UniquePtr<IGame>&& gameInstance, IGraphicsResourceManager& gfxResourceManager);

    public: // IOstEngine
        void Tick() override;
        void RenderSceneGraph(IRenderQueue& toQueue, const IRenderer& targetRenderer) override;

        InputReader& GetInputReader();

    private:
        Timer _timer;
        TimeStructure _timeData;
        GameWorld _gameWorld;
        InputReader _input;
        AssetManager _assetManager;

        OstEngineContext _context;

        UniquePtr<IGame> _gameInstance;
        Scene* _pActiveScene;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------