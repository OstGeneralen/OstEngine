// Kasper "OstGeneralen" Esbjornsson - 2026
#include "EditorContext.h"

using namespace ost;

EditorContext* EditorContext::_pInstance = nullptr;

// ------------------------------------------------------------

EditorContext& ost::EditorContext::Get()
{
    return *_pInstance;
}

void ost::EditorContext::Create(IOstEngine& engine, IGraphicsEngine& gfxEngine, const Window& win)
{
    _pInstance = new EditorContext(engine, gfxEngine, win);
}

void EditorContext::Destroy()
{
    delete _pInstance;
    _pInstance = nullptr;
}

EditorContext::EditorContext(IOstEngine& engine, IGraphicsEngine& gfxEngine, const Window& win)
    : coreEngine{engine}
    , graphicsEngine{gfxEngine}
    , window{win}
{
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------