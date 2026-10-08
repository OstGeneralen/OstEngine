// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <Engine/World/Component.h>

// ------------------------------------------------------------

class KeyboardMovementComponent : public ost::ActorComponent
{
public:
    KeyboardMovementComponent();

    void Update( ost::ComponentContext& context ) override;
};

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------