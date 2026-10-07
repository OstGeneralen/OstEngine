// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/Asset/GraphicsAssetsManager.h"
#include "Engine/EngineContext.h"
#include "Engine/Game/GameInterface.h"
#include "Engine/Game/Scene.h"
#include "Engine/System/InputReader.h"

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
        GraphicsAssetsManager& GetAssetManager() override;
        const TimeStructure& GetTime() const override;
        Scene& GetScene() override;
        const InputReader& GetInput() const;

    private:
        Timer _timer;
        TimeStructure _timeData;

        InputReader _input;

        UniquePtr<IGame> _gameInstance;

        GraphicsAssetsManager _gfxAssetManager;
        Scene _scene;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------