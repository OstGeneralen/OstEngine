// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/World/IScene.h"
#include "Engine/World/Transform.h"
#include "World/ComponentTicker.h"
#include "World/SceneGraph.h"

#include <Container/List.h>
#include <Memory/UniquePtr.h>
#include <Utility/StringID.h>

// ------------------------------------------------------------

namespace ost
{
    class Actor;
    class GameWorld;
    class ComponentTicker;

    struct PendingComponentDestroyEntry
    {
        Actor* pActor = nullptr;
        TypeID componentTypeId;
    };

    class Scene : public IScene
    {
    public:
        Scene();
        ~Scene();

        // BEGIN IScene
        Actor* CreateActor() override;
        void DestroyActor(Actor* pActor) override;

        List<UniquePtr<Actor>>& GetActors() override;
        const List<UniquePtr<Actor>>& GetActors() const override;
        // END IScene

        void Tick(ServiceLocator& serviceLocator);

        void MarkComponentForDestroy(Actor& actor, TypeID componentType);

        SceneGraph& GetSceneGraph();
        ComponentTicker& GetComponentTicker();

    private:
        List<UniquePtr<Actor>> _actors;

        // Pending lists for deferred destroys
        List<UniquePtr<Actor>> _pendingRemovalActors;
        List<PendingComponentDestroyEntry> _pendingComponentRemovals;

        SceneGraph _sceneGraph;
        ComponentTicker _componentTicker;

        StringID _nameId;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------