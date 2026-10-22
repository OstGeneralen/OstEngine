// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/Asset/IAssetManager.h"
#include "Engine/IOstEngine.h"
#include "Engine/World/IComponentFactory.h"

#include <OstTypes.h>

#include <Memory/UniquePtr.h>

// ------------------------------------------------------------

namespace ost
{
    class GameBase;
    extern UniquePtr<GameBase> CreateGameInstance();

    class GameBase
    {
    public:
        virtual ~GameBase() = default;

        virtual void Start(IComponentFactory& componentFactory) = 0;
        virtual void Shutdown(IComponentFactory& componentFactory) = 0;

        virtual void Load(IAssetManager& assetManager) = 0;
        virtual void Unload(IAssetManager& assetManager) = 0;
        virtual void Update(Float32 deltaTime) = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------