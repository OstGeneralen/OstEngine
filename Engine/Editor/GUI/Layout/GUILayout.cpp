// Kasper "OstGeneralen" Esbjornsson - 2026
#include "GUILayout.h"

#include "GUIMainMenu.h"

#include <Math/Color.h>

using namespace ost;

// ------------------------------------------------------------

void ost::GUILayout::PreWarmGUI(const Vector2f& renderSize, EditorContext& context)
{
    // This is really just a dry run of the whole layout, allowing all of the internal state to initialize its sizing
    ImGui::NewFrame();

    BeginGUIDraw(renderSize, context);
    PreWarmPanelChildrenGUI(_pRootPanel, context);
    EndGUIDraw();

    ImGui::EndFrame();
}

// ------------------------------------------------------------

void GUILayout::DrawGUI(const Vector2f& renderSize, EditorContext& context)
{
    BeginGUIDraw(renderSize, context);
    DrawPanelChildren(_pRootPanel, context);
    EndGUIDraw();
}

// ------------------------------------------------------------

void GUILayout::AddPanel(UniquePtr<GUIPanel>&& panel, const char* uniqueName, const Vector2f& normSize)
{
    GUIPanel* pPanel = _panels.Insert(uniqueName, std::move(panel)).Get();
    pPanel->_stringID = uniqueName;
    pPanel->_size = normSize;
}

// ------------------------------------------------------------

void ost::GUILayout::BeginGUIDraw(const Vector2f& renderSize, EditorContext& context)
{
    // 1. Draw the top level menu
    GUIMainMenu mainMenu;
    mainMenu.DrawGUI(context);

    const Float32 mainMenuHeight = ImGui::GetItemRectSize().y;
    const Vector2f remainingSize = {renderSize.X, renderSize.Y - mainMenuHeight};

    // 1. Set up all style state
    ImGuiWindowFlags flags = 0;
    flags |= ImGuiWindowFlags_NoDecoration;
    flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);         // Root window should not be rounded
    ImGui::PushStyleColor(ImGuiCol_WindowBg, Colors::Black.Vec4); // Root window has plain black background

    ImGui::SetNextWindowPos({0, mainMenuHeight}, 0, {0, 0}); // The root window should always be drawn at 0,0
    ImGui::SetNextWindowSize(remainingSize);                 // ...and fill the whole render area

    // 2. Begin the window
    ImGui::Begin("##GUIRoot", 0, flags);

    // 3. Pop the style state
    ImGui::PopStyleVar(1);
    ImGui::PopStyleColor();
}

void ost::GUILayout::EndGUIDraw()
{
    ImGui::End();
}

// ------------------------------------------------------------

void ost::GUILayout::PreWarmPanelChildrenGUI(GUIPanel* pPanel, EditorContext& context)
{
    const Vector2f availableArea = ImGui::GetContentRegionAvail();
    const Vector2f itemSpacing = ImGui::GetStyle().ItemSpacing;
    const SizeType numChildren = pPanel->_children.GetSize();
    const Float32 numChildrenFlt = static_cast<Float32>(numChildren);

    const Vector2f totalSpacing = numChildren > 0 ? itemSpacing * (numChildrenFlt - 1.0f) : itemSpacing;
    const Vector2f childrenArea = availableArea - totalSpacing;

    ImGui::PushID(pPanel->_stringID.c_str());

    for (SizeType i = 0; i < pPanel->_children.GetSize(); ++i)
    {
        const bool isLastChild = (i + 1) == pPanel->_children.GetSize();
        GUIPanel* pChild = pPanel->_children[i];

        pChild->_size = {pChild->_size.X * childrenArea.X, pChild->_size.Y * childrenArea.Y};

        ImGuiChildFlags childFlags = pChild->GetDrawFlags();

        ImGui::BeginChild(pChild->_stringID.c_str(), pChild->_size, childFlags);
        pChild->DrawGUI(context);

        PreWarmPanelChildrenGUI(pChild, context);

        ImGui::EndChild();

        if (pPanel->_orientation == EGuiLayoutOrientation::Horizontal && !isLastChild)
        {
            ImGui::SameLine();
        }
    }

    ImGui::PopID();
}

// ------------------------------------------------------------

void ost::GUILayout::DrawPanelChildren(GUIPanel* pPanel, EditorContext& context)
{
    ImGui::PushID(pPanel->_stringID.c_str());

    for (SizeType i = 0; i < pPanel->_children.GetSize(); ++i)
    {
        const bool isLastChild = (i + 1) == pPanel->_children.GetSize();
        GUIPanel* pChild = pPanel->_children[i];

        ImGuiWindowFlags windowFlags = pChild->GetWindowFlags();
        ImGuiChildFlags childFlags = pChild->GetDrawFlags();

        if (isLastChild)
        {
            if (pPanel->_orientation == EGuiLayoutOrientation::Horizontal)
            {
                pChild->_size.X = 0.0f;
            }
            else if (pPanel->_orientation == EGuiLayoutOrientation::Vertical)
            {
                pChild->_size.Y = 0.0f;
            }
        }

        if (!isLastChild)
        {
            if (pPanel->_orientation == EGuiLayoutOrientation::Horizontal)
            {
                childFlags |= ImGuiChildFlags_ResizeX;
            }
            else if (pPanel->_orientation == EGuiLayoutOrientation::Vertical)
            {
                childFlags |= ImGuiChildFlags_ResizeY;
            }
        }

        ImGui::BeginChild(pChild->_stringID.c_str(), pChild->_size, childFlags, windowFlags);

        pChild->DrawGUI(context);

        DrawPanelChildren(pChild, context);

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