// Kasper "OstGeneralen" Esbjornsson - 2026
#include "EditorGUI.h"

#include <imgui.h>

#include <Utility/Assert.h>

using namespace ost;

EditorGUI* EditorGUI::_pInstance = nullptr;

// ------------------------------------------------------------

EditorGUI& EditorGUI::Get()
{
    return *_pInstance;
}

// ------------------------------------------------------------

EditorGUI::EditorGUI()
{
    OST_ASSERT(_pInstance == nullptr, "Only one instace of EditorGUI allowed");
    _pInstance = this;
}

EditorGUI::~EditorGUI()
{
    _pInstance = nullptr;
}

// ------------------------------------------------------------

void ost::EditorGUI::Display(const Vector2f& displayArea)
{
    if (!_modalStack.IsEmpty())
    {
        ImGui::BeginDisabled();
    }

    // Display Menu Bar
    ImGui::BeginMainMenuBar();
    if (ImGui::BeginMenu("File"))
    {
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Project"))
    {
        if (ImGui::BeginMenu("Scene"))
        {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Assets"))
        {
            ImGui::EndMenu();
        }
        ImGui::EndMenu();
    }
    if(ImGui::BeginMenu("View"))
    {
        ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();

    GUIRect guiRect;
    guiRect.position = {0, ImGui::GetItemRectSize().y};
    guiRect.size = {displayArea.X, displayArea.Y - guiRect.position.Y};

    // Display Regular Controls
    for (auto ctrl : _rootControls)
    {
        if(ctrl->_pParent == nullptr)
        {
            ImGui::Begin( ctrl->_name.c_str());
            ImGui::End();

        }
    }

    // Display Top Modal Window (if any)
    if (!_modalStack.IsEmpty())
    {
        ImGui::EndDisabled();
        _modalStack.Top()->Display();
    }
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------