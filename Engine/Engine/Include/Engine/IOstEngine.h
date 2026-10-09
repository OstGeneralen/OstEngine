// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <OstTypes.h>

#include <Memory/UniquePtr.h>

// ------------------------------------------------------------

namespace ost
{
    class IGame;
    class IRenderQueue;
    class IGraphicsResourceManager;
    class InputReader;
    class IRenderer;

    struct OstEngineSettings
    {
        UniquePtr<IGame> gameInstance;
        IGraphicsResourceManager* pGfxResourceManager;
    };

    class IOstEngine
    {
    public:
        static UniquePtr<IOstEngine> CreateNew(OstEngineSettings&& settings);

    public:
        virtual void Tick() = 0;
        virtual void RenderSceneGraph(IRenderQueue& toQueue, const IRenderer& targetRenderer) = 0;

        virtual InputReader& GetInputReader() = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------