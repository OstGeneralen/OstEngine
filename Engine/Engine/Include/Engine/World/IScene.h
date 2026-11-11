// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <Container/List.h>
#include <Memory/UniquePtr.h>

// ------------------------------------------------------------

namespace ost
{
    class Actor;
    class IRenderScene;

    class IScene
    {
    public:
        virtual Actor* CreateActor() = 0;
        virtual void DestroyActor(Actor* pActor) = 0;

        virtual List<UniquePtr<Actor>>& GetActors() = 0;
        virtual const List<UniquePtr<Actor>>& GetActors() const = 0;

        virtual void OutputToRenderScene(IRenderScene& scene) const = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------