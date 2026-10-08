// Kasper "OstGeneralen" Esbjornsson - 2026
#include "ComponentTicker.h"

#include "Component.h"

using namespace ost;

// ------------------------------------------------------------

TickerHandle ComponentTicker::RegisterTicked(ActorComponent& component)
{
    _startList.Add(&component);
    return _tickList.Add(&component);
}

void ost::ComponentTicker::UnregisterTicked(TickerHandle handle)
{
    _tickList.Remove(handle);
}

void ost::ComponentTicker::TickAll(ComponentContext& ctx)
{
    for (auto componentPtr : _startList)
    {
        componentPtr->Start(ctx);
    }
    _startList.Clear();
    
    for (auto componentPtr : _tickList.GetDenseList())
    {
        componentPtr->Update(ctx);
    }
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------