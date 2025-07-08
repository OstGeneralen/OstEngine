// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)

#include <OstEngine/Application/Application.h>

// LOGGING
#include <OstLog/CoreAPI.h>
#include <OstLog/Sinks/FileLogSink.h>
#include <OstLog/Sinks/ConsoleLogSink.h>

// ------------------------------------------------------------

int main(int argc, char* argv[])
{
    // Start up logging system
    ost::log::CFileLogSink fileLogSink("Logs/", "OstEngineLog");
    OstLogger_RegisterLogSink(fileLogSink);

    ost::log::CConsoleLogSink consoleLogSink;
    OstLogger_RegisterLogSink(consoleLogSink);

    OstLogger_RunLogger();
    
    ost::CApplication app{ ost::SAppCmdArgs{argv, argc} };
    app.Run();

    // Shutdown logging system
    OstLogger_PostShutdownSignal();
    OstLogger_AwaitShutdown();

    return 0;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------