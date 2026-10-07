// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <Engine/Game/GameInterface.h>
#include <Engine/Game/Actor.h>


// ------------------------------------------------------------

class Game : public ost::IGame
{
public:
    void Load(ost::EngineContext& context) override;
    void Unload(ost::EngineContext& context) override;

    void Update(ost::EngineContext& context) override;
private:
    ost::Actor* _cameraActor;
    ost::Actor* _meshActor;
};

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------