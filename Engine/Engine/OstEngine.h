// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/Asset/GraphicsAssetsManager.h"
#include "Engine/EngineContext.h"
#include "Engine/Game/GameInterface.h"
#include "Engine/System/InputReader.h"
#include "Engine/World/GameWorld.h"

#include <OstTypes.h>

#include <GraphicsEngine/Rendering/IRenderer.h>
#include <Memory/UniquePtr.h>
#include <Utility/Timer.h>

// ------------------------------------------------------------

namespace ost
{
    class IGraphicsResourceManager;

    class OstEngine : public EngineContext
    {
    public:
        OstEngine();
        ~OstEngine();

        void Initialize(UniquePtr<IGame>&& gameInstance, IGraphicsResourceManager& gfxResourceManager);
        void Tick();
        void RenderScene(IRenderer& renderer);

        InputReader& GetInputReader();

    public: // EngineContext
        GraphicsAssetsManager& AssetManager() override;
        const TimeStructure& Time() const override;
        const InputReader& GetInput() const;
        
        UniquePtr<Scene> CreateScene(bool makeActive) override;
        void SetActiveScene(Scene& scene) override;

    private:
        Timer _timer;
        TimeStructure _timeData;
        GameWorld _gameWorld;
        InputReader _input;
        
        UniquePtr<IGame> _gameInstance;
        Scene* _pActiveScene;

        GraphicsAssetsManager _gfxAssetManager;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------