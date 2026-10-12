// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <OstTypes.h>

#include <Memory/UniquePtr.h>

// ------------------------------------------------------------

namespace ost
{
    class InputReader;
    class IAssetManager;

    struct TimeStructure
    {
        Float32 deltaTime;
        Float32 clampedDeltaTime;
        Float64 totalTime;
    };

    class EngineContext
    {
    public:
        virtual ~EngineContext() = default;

        static EngineContext& Get();
        static void Provide(EngineContext& context);

        virtual const TimeStructure& Time() const = 0;
        virtual IAssetManager& Assets() = 0;

    private:
        static EngineContext* _pInstance;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------