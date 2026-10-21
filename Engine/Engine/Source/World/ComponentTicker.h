// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <Container/List.h>
#include <Container/SlotMap.h>
#include <Services/ServiceLocator.h>

// ------------------------------------------------------------

namespace ost
{
    class ActorComponent;

    class ComponentTicker
    {
    public: // IComponentTicker
        Uint64 RegisterTicked(ActorComponent& component);
        void UnregisterTicked(Uint64 handle);

        void TickAll(ServiceLocator& serviceLocator);

    private:
        List<ActorComponent*> _startList;
        SlotMap<ActorComponent*> _tickList;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------