// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/World/Component.h"

#include <Memory/UniquePtr.h>
#include <Utility/TypeID.h>

// ------------------------------------------------------------

namespace ost
{
    class WorldContext
    {
    public:
        virtual void RegisterComponent(Actor& actor, ActorComponent& component) = 0;
        virtual void UnregisterComponent(Actor& actor, ActorComponent& component) = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------