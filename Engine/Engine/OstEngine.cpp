// Kasper "OstGeneralen" Esbjornsson - 2026
#include "OstEngine.h"

#include "Game/GameInterface.h"

#include <Utility/Assert.h>

using namespace ost;

// ------------------------------------------------------------

OstEngine::OstEngine()
{
}

OstEngine::~OstEngine()
{
}

void ost::OstEngine::AssignToGameInstance(IGame& gameInstance)
{
    gameInstance._pEngine = this;
}

Scene& OstEngine::GetScene()
{
    return _scene;
}

const Scene& OstEngine::GetScene() const
{
    return _scene;
}

// ------------------------------------------------------------

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------