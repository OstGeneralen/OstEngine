// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)

#include <OstEngine/EngineInterface.h>
#include <OstEngine/Debug/Logging/LogLevel.h>
#include <OstEngine/Debug/Logging/LogMessage.h>
#include <OstEngine/Debug/Logging.h>

// ------------------------------------------------------------

#include <iostream>
#include <unordered_map>

#if _WIN32
#include <Windows.h>
namespace log_helper
{
    const std::unordered_map<ost::ELogLevel, int> LEVEL_COL_MAP = {
        { ost::ELogLevel::Verbose,  7 },
        { ost::ELogLevel::Log,      7 },
        { ost::ELogLevel::Confirm,  10 },
        { ost::ELogLevel::Info,     7 },
        { ost::ELogLevel::Warning,  14 },
        { ost::ELogLevel::Error,    12 }
    };

    void ResetOutputColor()
    {
        HANDLE cHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(cHandle, 8);
    }

    void SetOutputColorForLogLevel(ost::ELogLevel level)
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

namespace log_helper
{
    std::string GetLevelString(ost::ELogLevel level)
    {
        switch (level)
        {
        case ost::ELogLevel::Log: return "MSG";
        case ost::ELogLevel::Verbose: return "VER";
        case ost::ELogLevel::Confirm: return "CON";
        case ost::ELogLevel::Info: return "INF";
        case ost::ELogLevel::Warning: return "WRN";
        case ost::ELogLevel::Error: return "ERR";
        }
        return "";
    }
}

#include <iostream>
class IOStreamLogger : public ost::ILogger
{
public:
    void ReceiveMessage(const ost::SLogMessage& msg, ost::uint32 scope) override
    {
        if (scope == 0)
        {
            log_helper::ResetOutputColor();
            std::cout << "[" << msg.FormatTimestamp(ost::ETimestampFormat::HH_MM_SS) << "] ";
            log_helper::SetOutputColorForLogLevel(msg.Level);
            std::cout << msg.Message << std::endl;
        }
        else
        {
            log_helper::ResetOutputColor();
            std::cout << "           \t" << msg.Message << std::endl;
        }
    }
};

// ------------------------------------------------------------

int main(int argc, char* argv[])
{
    IOStreamLogger iosLog;
    
    ost::SCommandArgs cmdArgs(argv, argc);
    ost::SEngineInitializationOptions initializeOpt = {};
    initializeOpt.InitLogger = &iosLog;
    initializeOpt.CmdLineArgs = &cmdArgs;

    ost::IOstEngine* engineInstancePtr = ost::CreateEngineInstance(initializeOpt);
    engineInstancePtr->Run();
    ost::ReleaseEngineInstance(&engineInstancePtr);
    return 0;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------