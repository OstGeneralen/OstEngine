// Kasper "OstGeneralen" Esbjornsson - 2026
#include "OstEngine.h"

#include <Utility/Assert.h>
#include <GraphicsEngine/GraphicsEngine.h>

ost::OstEngine* ost::pEngine = nullptr;


using namespace ost;

// ------------------------------------------------------------

OstEngine::OstEngine()
{
    OST_ASSERT(pEngine == nullptr, "Only one engine instance allowed per runtime");
    pEngine = this;
    _graphicsEngine = Ptr::NewUnique<GraphicsEngine>();
}

OstEngine::~OstEngine()
{
    pEngine = nullptr;
}

// ------------------------------------------------------------

GraphicsEngine& ost::OstEngine::GetGraphicsEngine()
{
    return *_graphicsEngine;
}

const GraphicsEngine& ost::OstEngine::GetGraphicsEngine() const
{
    return *_graphicsEngine;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------