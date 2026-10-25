// Kasper "OstGeneralen" Esbjornsson - 2026
#include "World/ComponentTicker.h"

#include "Engine/System/ITimeProvider.h"
#include "Engine/World/Component.h"

using namespace ost;

// ------------------------------------------------------------

Uint64 ComponentTicker::RegisterTicked(ActorComponent& component)
{
    _startList.Add(&component);
    return _tickList.Add(&component);
}

void ost::ComponentTicker::UnregisterTicked(Uint64 handle)
{
    _tickList.Remove(handle);
}

void ost::ComponentTicker::TickAll(ServiceLocator& services)
{
    const Float32 deltaTime = services.GetRequired<ITimeProvider>().GetDeltaTime();

    for (auto componentPtr : _startList)
    {
        componentPtr->Start();
    }
    _startList.Clear();

    for (auto componentPtr : _tickList.GetDenseList())
    {
        componentPtr->Update(deltaTime);
    }
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------