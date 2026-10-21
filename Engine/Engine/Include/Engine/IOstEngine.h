// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <OstTypes.h>

#include <Memory/UniquePtr.h>
#include <Services/ServiceLocator.h>

// ------------------------------------------------------------

namespace ost
{
    class GameBase;
    class IRenderQueue;
    class InputReader;
    class IRenderer;
    class IGraphicsEngine;

    // ------------------------------------------------------------
    // Globally available ptr to the engine to allow global access
    // to the service locator

    class IEngineGlobal
    {
        public:
        virtual ServiceLocator& GetServiceLocator() = 0;
    };
    extern IEngineGlobal* pEngine;

    // ------------------------------------------------------------

    class IOstEngine : public IEngineGlobal
    {
    public:
        static UniquePtr<IOstEngine> Create(ServiceLocator& appServiceLocator);

    public:
        virtual void SetGameInstance(GameBase* pGameInstance) = 0;

        virtual void Tick() = 0;
        virtual void RenderSceneGraph(IRenderQueue& toQueue, const IRenderer& targetRenderer) = 0;

        virtual InputReader& GetInputReader() = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------