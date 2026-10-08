// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/Game/Transform.h"

#include <Container/List.h>
#include <Memory/UniquePtr.h>

// ------------------------------------------------------------

namespace ost
{
    class WorldContext;
    class Actor;

    class Scene
    {
    public:
        Scene(WorldContext& worldContext);

        Actor* CreateActor();

    private:
        List<UniquePtr<Actor>> _actors;
        WorldContext& _worldContext;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------