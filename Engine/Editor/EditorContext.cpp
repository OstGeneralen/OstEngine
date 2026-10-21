// Kasper "OstGeneralen" Esbjornsson - 2026
#include "EditorContext.h"

using namespace ost;

EditorContext* EditorContext::_pInstance = nullptr;

// ------------------------------------------------------------

EditorContext& ost::EditorContext::Get()
{
    return *_pInstance;
}

void ost::EditorContext::Create(ServiceLocator& sl, const Window& win)
{
    _pInstance = new EditorContext(sl, win);
}

void EditorContext::Destroy()
{
    delete _pInstance;
    _pInstance = nullptr;
}

EditorContext::EditorContext(ServiceLocator& sl, const Window& win)
    : serviceLocator{sl}
    , window{win}
{
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------