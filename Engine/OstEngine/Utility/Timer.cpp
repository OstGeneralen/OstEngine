#include "Timer.h"

ost::CTimer::CTimer()
    : _firstTimePoint{ std::chrono::high_resolution_clock::now() }
    , _previousTimePoint{ std::chrono::high_resolution_clock::now() }
    , _currentTotalTime{ 0 }
    , _currentDeltaTime{ 0.f }
{
}

void ost::CTimer::Update()
{
    std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<Float32> duration = now - _previousTimePoint;
    std::chrono::duration<Float64> totalDuration = now - _firstTimePoint;

    _currentDeltaTime = duration.count();
    _currentTotalTime = totalDuration.count();
}

Float32 ost::CTimer::GetDeltaTime() const
{
    return _currentDeltaTime;
}

Float64 ost::CTimer::GetTotalTime() const
{
    return _currentTotalTime;
}