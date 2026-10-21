// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <Engine/World/Component.h>
#include <Engine/System/IInputReader.h>

// ------------------------------------------------------------

class KeyboardMovementComponent : public ost::ActorComponent
{
public:
    KeyboardMovementComponent();

    void Update(Float32 deltaTime) override;

private:
    const ost::IInputReader& _input;

};

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------