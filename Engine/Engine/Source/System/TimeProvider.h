// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/System/ITimeProvider.h"

#include <OstTypes.h>

#include <Utility/Timer.h>

// ------------------------------------------------------------

namespace ost
{
    class TimeProvider : public ITimeProvider
    {
    public:
        void Update();

        // BEGIN ITimeProvider
        Float32 GetDeltaTime() const override;
        Float32 GetClampedDeltaTime() const override;
        Float64 GetTotalTime() const override;
        // END ITimeProvider

    private:
        Timer _timer;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------