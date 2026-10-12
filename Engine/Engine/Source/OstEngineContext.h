// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/Asset/IAssetManager.h"
#include "Engine/EngineContext.h"

// ------------------------------------------------------------

namespace ost
{
    class Timer;

    class OstEngineContext : public EngineContext
    {
    public:
        OstEngineContext(IAssetManager& assetManager);

        void UpdateTime(const Timer& timer);

        // BEGIN EngineContext
        const TimeStructure& Time() const override;
        IAssetManager& Assets() override;
        // END EngineContext

    private:
        IAssetManager& _assetManager;
        TimeStructure _timeStructure;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------