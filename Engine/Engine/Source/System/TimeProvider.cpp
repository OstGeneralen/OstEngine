// Kasper "OstGeneralen" Esbjornsson - 2026
#include "TimeProvider.h"

using namespace ost;

// ------------------------------------------------------------

void TimeProvider::Update()
{
    _timer.Tick();
}

// ------------------------------------------------------------

Float32 ost::TimeProvider::GetDeltaTime() const
{
    return _timer.GetDeltaTime();
}

Float32 ost::TimeProvider::GetClampedDeltaTime() const
{
    return _timer.GetRestrictedDeltaTime();
}

Float64 ost::TimeProvider::GetTotalTime() const
{
    return _timer.GetTotalTime();
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------