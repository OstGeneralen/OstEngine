// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/Asset/GraphicsAssetsManager.h"
#include "Engine/EngineContext.h"
#include "Engine/Game/GameInterface.h"
#include "Engine/Game/Scene.h"

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

    public: // EngineContext
        GraphicsAssetsManager& GetAssetManager() override;
        const TimeStructure& GetTime() const override;
        Scene& GetScene() override;

    private:
        Timer _timer;
        TimeStructure _timeData;

        UniquePtr<IGame> _gameInstance;

        GraphicsAssetsManager _gfxAssetManager;
        Scene _scene;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------