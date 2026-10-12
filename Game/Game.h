// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <Engine/Game/GameInterface.h>
#include <Engine/World/Scene.h>
#include <Memory/UniquePtr.h>


// ------------------------------------------------------------

// ------------------------------------------------------------

class Game : public ost::IGame
{
public:
    void Load(ost::GameContext& context) override;
    void Unload(ost::GameContext& context) override;

    void Update(ost::GameContext& context) override;

private:
    ost::UniquePtr<ost::Scene> _scene;
};

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------