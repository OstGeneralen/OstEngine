// Kasper "OstGeneralen" Esbjornsson - 2026
#include "AboutWindow.h"

#include "EditorContext.h"
#include "GUI/IEditorGUI.h"

#include <imgui.h>

using namespace ost;

// ------------------------------------------------------------

void AboutWindow::DrawGUI(EditorContext& context)
{
    bool wasOpen = _isOpen;

    ImGui::SetNextWindowSizeConstraints({200, 200}, {800, 800});

    ImGui::Begin("About##GUIWindow", &_isOpen);

    ImGui::TextColored({1, 1, 0, 1}, "Ost Engine Editor");
    ImGui::Separator();
    ImGui::TextWrapped("This text is honestly mostly here because I wanted to have a window to display.");
    ImGui::TextWrapped("Might write more here at a later date.");
    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::TextWrapped("IDK.");
    ImGui::Spacing();
    ImGui::Text("// OstGeneralen");

    ImGui::End();

    if (wasOpen && !_isOpen)
    {
        context.serviceLocator.GetRequired<IEditorGUI>().CloseWindow<AboutWindow>();
    }
}

void ost::AboutWindow::OnOpen(EditorContext& context)
{
    _isOpen = true;
}

void ost::AboutWindow::OnClose(EditorContext& context)
{
    _isOpen = false;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------