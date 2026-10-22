// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/World/Transform.h"

#include <Container/List.h>
#include <Memory/UniquePtr.h>

// ------------------------------------------------------------

namespace ost
{
    class Actor;
    class GameWorld;

    class Scene
    {
    public:
        Scene(GameWorld& gameWorld);
        ~Scene();

        Actor* CreateActor();
        void DestoryActor( Actor* pActor );

        List<UniquePtr<Actor>>& GetAllActors();
        const List<UniquePtr<Actor>>& GetAllActors() const;

    private:
        List<UniquePtr<Actor>> _actors;
        GameWorld& _gameWorld;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------