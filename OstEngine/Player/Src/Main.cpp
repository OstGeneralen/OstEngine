// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)

#include <OstEngine/EngineInterface.h>

#include <OstLog/OstLogger.h>
#include <OstLog/MessageFormatter.h>
#include <OstLog/Sinks/ConsoleLogSink.h>
#include <OstLog/Sinks/FileLogSink.h>
#include <OstLog/LoggerLifetimeManagement.h>

// ------------------------------------------------------------

OSTLOG_LOG_INSTANCE(AppLog);

// ------------------------------------------------------------

int main(int argc, char* argv[])
{
    ost::log::CConsoleLogSink consoleLogSink;
    ost::log::CFileLogSink fileLogSink{ "Logs/", "OstEngineLog" };

    auto& logger = GetLogger();
    OstLogger_RegisterLogSink(consoleLogSink);
    OstLogger_RegisterLogSink(fileLogSink);

    ost::SCommandArgs cmdArgs(argv, argc);
    ost::SEngineInitializationOptions initializeOpt = {};
    //initializeOpt.InitLogger = &iosLog;
    initializeOpt.CmdLineArgs = &cmdArgs;

    OstLogger_RunLogger();

    AppLog.Log(OstLogLevel::Info, "Application bootflow initialized. Creating engine instance");
    ost::IOstEngine* engineInstancePtr = ost::CreateEngineInstance(initializeOpt);
    engineInstancePtr->Run();
    ost::ReleaseEngineInstance(&engineInstancePtr);

    OstLogger_PostShutdownSignal();
    OstLogger_AwaitShutdown();

    return 0;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------