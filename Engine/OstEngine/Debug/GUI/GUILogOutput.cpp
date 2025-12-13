#include "GUILogOutput.h"

#include <OstEngine/Debug/Logging/Logger.h>
#include <OstEngine/ImGui/imgui.h>

bool ost::gui::GUI_LogOutput::Expanded = false;

void ost::gui::GUI_LogOutput::Display()
{
    for (const auto& msg : log::CLogger::Instance())
    {
        ImVec4 textColor = { 0.75f, 0.75f, 0.75f, 1.0f};
        switch ( msg.Verbosity )
        {
        case log::ELogLevel::Confirm:
            textColor = { 0.1f, 0.8f, 0.15f, 1.0f };
            break;
        case log::ELogLevel::Warning:
            textColor = { 0.1f, 0.8f, 0.8f, 1.0f };
            break;
        case log::ELogLevel::Error:
            textColor = { 0.8f, 0.1f, 0.1f, 1.0f };
            break;
        }

        ImGui::TextColored( textColor, "[%s] %s", msg.FormattedTime.c_str(), msg.Message.c_str() );
    }
}

void ost::gui::GUI_LogOutput::DisplayStandalone()
{
    ImGui::SetNextWindowSize( { 0, 250 } );
    ImGui::Begin( "StandaloneLoggingOutput", nullptr, ImGuiWindowFlags_NoSavedSettings );
    Display();
    ImGui::End();
}