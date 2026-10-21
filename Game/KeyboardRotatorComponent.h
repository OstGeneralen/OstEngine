// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <Engine/System/InputReader.h>
#include <Engine/World/Component.h>

// ------------------------------------------------------------

class KeyboardRotatorComponent : public ost::ActorComponent
{
public:
    KeyboardRotatorComponent();

    void Update(Float32 deltaTime) override;

private:
    ost::IInputReader& _input;

};

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------