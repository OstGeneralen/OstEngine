// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <OstTypes.h>

// ------------------------------------------------------------

namespace ost
{
    class ITimeProvider
    {
    public:
        virtual ~ITimeProvider() = default;

        virtual Float32 GetDeltaTime() const = 0;
        virtual Float32 GetClampedDeltaTime() const = 0;
        virtual Float64 GetTotalTime() const = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------