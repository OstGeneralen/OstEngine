// Kasper "OstGeneralen" Esbjornsson - 2026
#include "GUILayout.h"

#include <Math/Color.h>

using namespace ost;

// ------------------------------------------------------------

void GUILayout::InitializeSizing(const Vector2f& renderSize)
{
    InitializeChildSize(_pRootPanel, renderSize);
}

// ------------------------------------------------------------

void GUILayout::DrawGUI(const Vector2f& renderSize, EditorContext& context)
{
    GUIRect renderRect;
    renderRect.min = {0, 0};
    renderRect.max = renderSize;

    ImGuiWindowFlags flags = 0;
    flags |= ImGuiWindowFlags_NoDecoration;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0, 0});     // Root window should not be padded
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, {0, 0});    // Root window should not be rounded
    ImGui::PushStyleColor(ImGuiCol_WindowBg, Colors::Black.Vec4); // Root window has plain black background

    // Begin the window
    ImGui::Begin("##GUIRoot", 0, flags);

    ImGui::PopStyleVar(2);
    ImGui::PopStyleColor();

    DrawPanelChildren(_pRootPanel, context);

    ImGui::End();
}

// ------------------------------------------------------------

void GUILayout::AddPanel(UniquePtr<GUIPanel>&& panel, const char* uniqueName, const Vector2f& normSize)
{
    GUIPanel* pPanel = _panels.Insert(uniqueName, std::move(panel)).Get();
    pPanel->_size = normSize;
}

// ------------------------------------------------------------

void ost::GUILayout::InitializeChildSize(GUIPanel* pChild, const Vector2f& parentSize)
{
    const Vector2f childNormSize = pChild->_size;
    pChild->_size = {childNormSize.X * parentSize.X, childNormSize.Y * parentSize.Y};

    switch (pChild->_orientation)
    {
    case EGuiLayoutOrientation::Vertical: { // Full width, percentage of height
        pChild->_size.X = parentSize.X;
        break;
    }
    case EGuiLayoutOrientation::Horizontal: { // Full height, percentage of width
        pChild->_size.Y = parentSize.Y;
        break;
    }
    }

    // Recursively iterate through the childrent and adjust their sizes according to this child's size
    for (auto pGrandChild : pChild->_children)
    {
        InitializeChildSize(pGrandChild, pChild->_size);
    }
}

// ------------------------------------------------------------

void ost::GUILayout::DrawPanelChildren(GUIPanel* pPanel, EditorContext& context)
{
    ImGui::PushID(pPanel->_stringID.c_str());

    for (SizeType i = 0; i < pPanel->_children.GetSize(); ++i)
    {
        const bool isLastChild = (i + 1) == pPanel->_children.GetSize();
        GUIPanel* pChild = pPanel->_children[i];

        ImGuiChildFlags childFlags = pChild->GetDrawFlags();

        ImGui::BeginChild(pChild->_stringID.c_str(), pChild->_size, childFlags);
        pChild->DrawGUI(context);
        ImGui::EndChild();

        if (pPanel->_orientation == EGuiLayoutOrientation::Horizontal && !isLastChild)
        {
            ImGui::SameLine();
        }
    }

    ImGui::PopID();
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------