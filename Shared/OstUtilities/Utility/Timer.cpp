// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Timer.h"

#include <Math/Math.h>

using namespace ost;

// ------------------------------------------------------------

Timer::Timer()
    : _startTimePoint{std::chrono::high_resolution_clock::now()}
    , _lastTimePoint{_startTimePoint}
    , _cachedTotalTime{0.0}
    , _cachedDeltaTime{0.0f}
{
}

Float32 Timer::GetDeltaTime() const
{
    return _cachedDeltaTime;
}

Float32 Timer::GetRestrictedDeltaTime(Float32 maxValue) const
{
    return math::Clamp(_cachedDeltaTime, 0.0f, maxValue);
}

Float64 Timer::GetTotalTime() const
{
    return _cachedTotalTime;
}

void Timer::Tick()
{
    auto now = std::chrono::high_resolution_clock::now();

    const std::chrono::duration<Float32> deltaTimeDuration = now - _lastTimePoint;
    const std::chrono::duration<Float64> totalTimeDuration = now - _startTimePoint;

    _cachedTotalTime = totalTimeDuration.count();
    _cachedDeltaTime = deltaTimeDuration.count();

    _lastTimePoint = now;
}
// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------