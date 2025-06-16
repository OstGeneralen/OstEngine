// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)

#include <OstEngine/EngineInterface.h>

#include <OstLog/OstLogger.h>
#include <OstLog/MessageFormatter.h>
#include <OstLog/Sinks/LogSink.h>
#include <OstLog/LoggerLifetimeManagement.h>

// ------------------------------------------------------------

#include <iostream>
#include <unordered_map>

#if _WIN32
#include <Windows.h>
namespace log_helper
{
    //const std::unordered_map<ost::ELogLevel, int> LEVEL_COL_MAP = {
    //    { ost::ELogLevel::Verbose,  7 },
    //    { ost::ELogLevel::Log,      7 },
    //    { ost::ELogLevel::Confirm,  10 },
    //    { ost::ELogLevel::Info,     7 },
    //    { ost::ELogLevel::Warning,  14 },
    //    { ost::ELogLevel::Error,    12 }
    //};
    //
    //void ResetOutputColor()
    //{
    //    HANDLE cHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    //    SetConsoleTextAttribute(cHandle, 8);
    //}
    //
    //void SetOutputColorForLogLevel(ost::ELogLevel level)
    //{
    //    HANDLE cHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    //    SetConsoleTextAttribute(cHandle, LEVEL_COL_MAP.at(level));
    //}
}

#else
namespace log_helper
{
    void ResetOutputColor() {}
    void SetOutputColorForLogLevel(ost::ELogLevel level) {}
}
#endif

#include <iostream>
class IOStreamLogger : public ost::log::CLogSink
{
public:
    void Log(const ost::log::SLogMessage& msg) override
    {
        ost::log::SMessageFormatter fmt(msg);
        std::cout << "[" << fmt.LevelStr_Abbr() << "] " << fmt.TimeStr_HHMMSS() << ": " << fmt.MessageStr() << std::endl;
    }
};

// ------------------------------------------------------------

int main(int argc, char* argv[])
{
    IOStreamLogger iosLog;
    
    auto& logger = GetLogger();
    OstLogger_RegisterLogSink(iosLog);

    ost::SCommandArgs cmdArgs(argv, argc);
    ost::SEngineInitializationOptions initializeOpt = {};
    //initializeOpt.InitLogger = &iosLog;
    initializeOpt.CmdLineArgs = &cmdArgs;

    OstLogger_RunLogger();

    logger.INFO("Test info message with integer {}", 10);
    logger.DEBUG("Test debug message with integer {}", 50);
    logger.WARNING("Test warning message with integer {}", 20);

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