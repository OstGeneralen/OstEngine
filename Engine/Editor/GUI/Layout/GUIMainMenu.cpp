// Kasper "OstGeneralen" Esbjornsson - 2026
#include "GUIMainMenu.h"

#include "EditorContext.h"
#include "GUI/Window/AboutWindow.h"
#include "GUI/Window/OpenWindowCommand.h"
#include "System/IEditorCommandQueue.h"

#include <imgui.h>

using namespace ost;

// ------------------------------------------------------------

void GUIMainMenu::DrawGUI(EditorContext& context)
{

    ImGui::BeginMainMenuBar();

    if (ImGui::BeginMenu("File"))
    {
        if (ImGui::MenuItem("New"))
        {
        }
        if (ImGui::MenuItem("Save"))
        {
        }
        if (ImGui::MenuItem("Load"))
        {
        }
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Project"))
    {
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Options"))
    {
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("About"))
    {
        if (ImGui::MenuItem("About Window"))
        {
            context.commandQueue.PushCommand(OpenWindowEditorCommand::ForWindowType<AboutWindow>());
        }
        ImGui::EndMenu();
    }

    ImGui::EndMainMenuBar();
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------