#pragma once
#include <OstEngine/Types.h>
#include <chrono>

namespace ost
{
    class CTimer
	{
    public:
        CTimer();
        CTimer( const CTimer& ) = delete;

        void Update();

        Float32 GetDeltaTime() const;
        Float64 GetTotalTime() const; 
    private:
        std::chrono::high_resolution_clock::time_point _firstTimePoint;
        std::chrono::high_resolution_clock::time_point _previousTimePoint;

        Float64 _currentTotalTime;
        Float32 _currentDeltaTime;
	};
}