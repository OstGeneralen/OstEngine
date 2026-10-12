// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <Engine/World/Component.h>

// ------------------------------------------------------------

class KeyboardRotatorComponent : public ost::ActorComponent
{
public:
    KeyboardRotatorComponent();

    void Update(ost::ComponentContext& context) override;
};

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------