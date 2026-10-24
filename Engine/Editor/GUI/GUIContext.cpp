// Kasper "OstGeneralen" Esbjornsson - 2026
#include "GUIContext.h"

#include "EditorContext.h"

using namespace ost;

// ------------------------------------------------------------

GUIContext::GUIContext(EditorContext& parentCtx, EditorGUI& gui)
    : _parentContext{parentCtx}
    , _gui{gui}
{
}

// ------------------------------------------------------------

void ost::GUIContext::OpenWindow(TypeID windowType)
{
    _gui.OpenWindow(windowType);
}

void ost::GUIContext::CloseWindow(TypeID windowType)
{
    _gui.CloseWindow(windowType);
}

// ------------------------------------------------------------

void GUIContext::OpenContextMenu(IGUIContextMenuOwner& menuOwner)
{
    _gui.OpenContextMenu(menuOwner);
}

void GUIContext::CloseContextMenu()
{
    _gui.CloseContextMenu();
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------