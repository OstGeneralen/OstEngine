// Kasper "OstGeneralen" Esbjornsson - 2026
#include "OstEngineContext.h"

#include <Utility/Timer.h>

using namespace ost;

// ------------------------------------------------------------

EngineContext* EngineContext::_pInstance = nullptr;

EngineContext& EngineContext::Get()
{
    return *_pInstance;
}

void EngineContext::Provide(EngineContext& ctx)
{
    _pInstance = &ctx;
}

// ------------------------------------------------------------

OstEngineContext::OstEngineContext(IAssetManager& assetManager)
    : _assetManager{assetManager}
    , _timeStructure{}
{
    EngineContext::Provide(*this);
}

void OstEngineContext::UpdateTime(const Timer& timer)
{
    _timeStructure.clampedDeltaTime = timer.GetRestrictedDeltaTime();
    _timeStructure.deltaTime = timer.GetDeltaTime();
    _timeStructure.totalTime = timer.GetTotalTime();
}

const TimeStructure& OstEngineContext::Time() const
{
    return _timeStructure;
}

IAssetManager& OstEngineContext::Assets()
{
    return _assetManager;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------