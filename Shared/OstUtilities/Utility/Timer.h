// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <OstTypes.h>
#include <chrono>

// ------------------------------------------------------------

namespace ost
{
    class Timer
    {
    public:
        Timer();
        Timer(const Timer&) = delete;

        Float32 GetDeltaTime() const;
        Float32 GetRestrictedDeltaTime(Float32 maxValue = 1.0f) const;

        Float64 GetTotalTime() const;

        void Tick();

    private:
        std::chrono::high_resolution_clock::time_point _startTimePoint;
        std::chrono::high_resolution_clock::time_point _lastTimePoint;
        Float64 _cachedTotalTime;
        Float32 _cachedDeltaTime;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------