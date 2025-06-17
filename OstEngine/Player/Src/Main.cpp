// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)

#include <OstEngine/EngineInterface.h>

#include <OstLog/OstLogger.h>
#include <OstLog/MessageFormatter.h>
#include <OstLog/Sinks/LogSink.h>
#include <OstLog/LoggerLifetimeManagement.h>

// ------------------------------------------------------------

OSTLOG_LOG_INSTANCE(AppLog);

#include <iostream>
#include <iomanip>
#include <unordered_map>

#if _WIN32
#include <Windows.h>
namespace log_helper
{
    constexpr static int DarkGrey = 8;
    constexpr static int LightGrey = 7;
    constexpr static int White = 15;
    constexpr static int Green = 10;
    constexpr static int Cyan = 11;
    constexpr static int Red = 12;
    constexpr static int Yellow = 14;
    constexpr static int Purple = 13;

    const std::unordered_map<ost::log::ELogLevel, int> LEVEL_COL_MAP = {
        { ost::log::ELogLevel::Trace,     LightGrey },
        { ost::log::ELogLevel::Debug,     LightGrey },
        { ost::log::ELogLevel::Info,     Cyan },
        { ost::log::ELogLevel::Warning,  Yellow },
        { ost::log::ELogLevel::Error,    Red },
        { ost::log::ELogLevel::Fatal,    Purple },
    };
    
    void SetOutputColor_Detail()
    {
        HANDLE cHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(cHandle, DarkGrey);
    }

    void SetOutputColor_PrimaryMessage()
    {
        HANDLE cHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(cHandle, White);
    }

    void SetOutputColor_SecondaryMessage()
    {
        HANDLE cHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(cHandle, LightGrey);
    }
    
    void SetOutputColorForLogLevel(ost::log::ELogLevel level)
    {
        HANDLE cHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(cHandle, LEVEL_COL_MAP.at(level));
    }
}

#else
namespace log_helper
{
    void ResetOutputColor() {}
    void SetOutputColorForLogLevel(ost::ELogLevel level) {}
}
#endif

class IOStreamLogger : public ost::log::CLogSink
{
public:
    void Log(const ost::log::SLogMessage& msg) override
    {
        ost::log::SMessageFormatter fmt(msg);

        const int lvlW = 4;
        const int timeW = 9;
        const int msgIndent = lvlW + timeW;

        log_helper::SetOutputColorForLogLevel(msg.Level);
        std::cout << std::setw(lvlW) << std::left << fmt.LevelStr_Abbr();
        log_helper::SetOutputColor_Detail();
        std::cout << std::setw(timeW) << std::left << fmt.TimeStr_HHMMSS();

        log_helper::SetOutputColor_PrimaryMessage();
        std::cout << fmt.MessageStr() << std::endl;

        for (const ost::log::SLogMessage& sub : msg.SubMessages)
        {
            ost::log::SMessageFormatter subFmt(sub);
            log_helper::SetOutputColor_Detail();
            std::cout << std::setw(msgIndent + 2) << std::right << "- ";
            log_helper::SetOutputColor_SecondaryMessage();
            std::cout <<  subFmt.MessageStr() << std::endl;
        }
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