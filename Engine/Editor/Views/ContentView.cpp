// Kasper "OstGeneralen" Esbjornsson - 2026
#include "ContentView.h"

#include <imgui.h>

using namespace ost;

// ------------------------------------------------------------

ost::ContentView::ContentView(UniquePtr<ViewContent>&& content)
    : _content{std::move(content)}
{
}

void ContentView::Present(const ViewRect& viewRect)
{
    if (!_content)
    {
        return;
    }

    ImGui::SetNextWindowPos(viewRect.position);
    ImGui::SetNextWindowSize(viewRect.size);
    ImGui::Begin(_content->GetName().c_str(), 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
    _content->Present(viewRect);
    ImGui::End();
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------