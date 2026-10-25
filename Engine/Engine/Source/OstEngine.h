// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Asset/AssetManager.h"
#include "Engine/Game/GameBase.h"
#include "Engine/IOstEngine.h"

// World
#include "World/SceneManager.h"
#include "World/ComponentFactory.h"

// System
#include "Engine/System/InputReader.h"
#include "System/TimeProvider.h"

#include <OstTypes.h>

#include <GraphicsEngine/Rendering/IRenderer.h>
#include <Memory/UniquePtr.h>
#include <Services/ServiceLocator.h>
#include <Utility/Timer.h>

// ------------------------------------------------------------

namespace ost
{
    class IGraphicsResourceManager;
    class IMaterialManager;

    class OstEngine;

    class OstEngine : public IOstEngine
    {
    public:
        OstEngine(ServiceLocator& appServiceLocator);
        ~OstEngine();

        // BEGIN IOstEngine
        void SetGameInstance(GameBase* pGameInstance) override;

        void Tick() override;
        void RenderSceneGraph(IRenderQueue& toQueue, const IRenderer& targetRenderer) override;

        virtual ServiceLocator& GetServiceLocator() override;
        InputReader& GetInputReader() override;
        // END IOstEngine


    private:
        ServiceLocator& _appServiceLocator;

        InputReader _input;
        TimeProvider _time;
        
        ComponentFactory _componentFactory;

        AssetManager _assetManager;
        SceneManager _sceneManager;

        GameBase* _pGameInstance;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------