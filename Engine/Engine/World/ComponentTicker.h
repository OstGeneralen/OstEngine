// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/World/IComponentTicker.h"

#include <Container/List.h>
#include <Container/SlotMap.h>

// ------------------------------------------------------------

namespace ost
{
    class ComponentTicker : public IComponentTicker
    {
    public: // IComponentTicker
        TickerHandle RegisterTicked(ActorComponent& component) override;
        void UnregisterTicked(TickerHandle handle) override;

        void TickAll(ComponentContext& ctx) override;

    private:
        List<ActorComponent*> _startList;
        SlotMap<ActorComponent*> _tickList;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------