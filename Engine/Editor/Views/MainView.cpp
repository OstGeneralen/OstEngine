// Kasper "OstGeneralen" Esbjornsson - 2026
#include "MainView.h"

using namespace ost;

// ------------------------------------------------------------

void MainView::SetRoot(UniquePtr<View>&& rootContent)
{
    _rootElement = std::move(rootContent);
}

void ost::MainView::Present(const Window& mainWindow)
{
    ViewRect viewRect;
    viewRect.position = {0, 0};
    viewRect.size = mainWindow.GetClientSize().VectorCast<Float32>();
    _rootElement->Present(viewRect);
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------