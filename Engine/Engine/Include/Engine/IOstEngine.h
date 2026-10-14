// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/Configuration/RuntimeConfig.h"

#include <OstTypes.h>

#include <Memory/UniquePtr.h>

// ------------------------------------------------------------

namespace ost
{
    class IGame;
    class IRenderQueue;
    class InputReader;
    class IRenderer;
    class IGraphicsEngine;

    struct OstEngineSettings
    {
        IGraphicsEngine* pGfxEngine;
        AssetsConfig assetsCfg;
    };

    class IOstEngine
    {
    public:
        static UniquePtr<IOstEngine> CreateNew(UniquePtr<IGame>&& gameInstance, const OstEngineSettings& settings);

    public:
        virtual void Tick() = 0;
        virtual void RenderSceneGraph(IRenderQueue& toQueue, const IRenderer& targetRenderer) = 0;

        virtual InputReader& GetInputReader() = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------