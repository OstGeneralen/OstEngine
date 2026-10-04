// Kasper "OstGeneralen" Esbjornsson - 2026
#include "OstEngine.h"

#include <Utility/Assert.h>

using namespace ost;

OstEngine* pEngine = nullptr;

// ------------------------------------------------------------

OstEngine::OstEngine()
{
    OST_ASSERT(pEngine == nullptr, "Only one engine instance allowed per runtime");
    pEngine = this;
}

OstEngine::~OstEngine()
{
    pEngine = nullptr;
}

// ------------------------------------------------------------

const GraphicsEngine& ost::OstEngine::GetGraphicsEngine() const
{
    return *_graphicsEngine;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------