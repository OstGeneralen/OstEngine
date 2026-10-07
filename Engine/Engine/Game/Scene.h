// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <Container/List.h>
#include <Container/Map.h>
#include <Memory/UniquePtr.h>
#include <Utility/TypeID.h>

// ------------------------------------------------------------

namespace ost
{
    class Component;
    class Actor;

    class Scene
    {
    public:
        Scene();
        ~Scene();

        Actor* NewActor();

        const List<UniquePtr<Actor>>& GetActors() const;

        void Update(Float32 deltaTime);

    private:
        List<UniquePtr<Actor>> _actors;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------