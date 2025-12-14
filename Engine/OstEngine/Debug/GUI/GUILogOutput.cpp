#include "GUILogOutput.h"

#include <OstEngine/Debug/Logging/Logger.h>
#include <OstEngine/ImGui/imgui.h>

bool ost::gui::GUI_LogOutput::Expanded = false;

void DisplayMessage( const ost::log::SLogMessage& aMsg, Int32 aLevel )
{
    ImVec4 textColor = { 0.75f, 0.75f, 0.75f, 1.0f };
    switch ( aMsg.Verbosity )
    {
    case ost::log::ELogLevel::Confirm:
        textColor = { 0.1f, 0.8f, 0.15f, 1.0f };
        break;
    case ost::log::ELogLevel::Warning:
        textColor = { 0.1f, 0.8f, 0.8f, 1.0f };
        break;
    case ost::log::ELogLevel::Error:
        textColor = { 0.8f, 0.1f, 0.1f, 1.0f };
        break;
    }

    if ( aLevel == 0 )
    {
        ImGui::TextColored( textColor, "[%s] %s", aMsg.FormattedTime.c_str(), aMsg.Message.c_str() );
    }
    else
    {
        std::stringstream msgStr;
        msgStr << ".......... ";
        for ( Int32 i = 0; i < aLevel; ++i )
        {
            msgStr << "    ";
        }
        msgStr << aMsg.Message;
        ImGui::TextColored( textColor, "%s", msgStr.str().c_str() );
    }

    for ( const auto& childMessage : aMsg.Inner )
    {
        DisplayMessage( childMessage, aLevel + 1 );
    }
}

void ost::gui::GUI_LogOutput::Display()
{
    for ( const auto& msg : log::CLogger::Instance() )
    {
        DisplayMessage( msg, 0 );
    }
}

void ost::gui::GUI_LogOutput::DisplayStandalone()
{
    ImGui::SetNextWindowSize( { 0, 250 } );
    ImGui::Begin( "StandaloneLoggingOutput", nullptr, ImGuiWindowFlags_NoSavedSettings );
    Display();
    ImGui::End();
}