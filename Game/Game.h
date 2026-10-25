// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <Engine/Game/GameBase.h>
#include <Engine/World/IScene.h>
#include <Memory/UniquePtr.h>

// ------------------------------------------------------------

// ------------------------------------------------------------

class Game : public ost::GameBase
{
public:
    void Start(ost::IComponentFactory& componentFactory) override;
    void Shutdown(ost::IComponentFactory& componentFactory) override;

    void Load(ost::IAssetManager& assets) override;
    void Unload(ost::IAssetManager& assets) override;
    void Update(Float32 deltaTime) override;

private:
};

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------