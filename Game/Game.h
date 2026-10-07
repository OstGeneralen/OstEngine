// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <Engine/Game/GameInterface.h>
#include <Engine/Game/Actor.h>


// ------------------------------------------------------------

class Game : public ost::IGame
{
public:
    void Load() override;
    void Unload() override;

    void Update(Float32 deltaTime) override;
private:
    ost::Actor* _cameraActor;
    ost::Actor* _meshActor;
};

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------