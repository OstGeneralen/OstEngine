// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/System/InputReader.h"

#include <OstTypes.h>

#include <Utility/Timer.h>

// ------------------------------------------------------------

namespace ost
{
    class ComponentContext
    {
    public:
        ComponentContext(const Timer& timer, InputReader& inputReader)
            : _time{timer.GetDeltaTime(), timer.GetRestrictedDeltaTime(), timer.GetTotalTime()}
            , _input{inputReader}
        {
        }

        struct TimeData
        {
            Float32 deltaTime;
            Float32 clampedDeltaTime;
            Float64 totalTime;
        };

        const TimeData& Time() const
        {
            return _time;
        }
        const InputReader& Input() const
        {
            return _input;
        }

    private:
        TimeData _time;
        InputReader& _input;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------