add_library(Logger SHARED)

target_sources(Logger PRIVATE 
    "Src/Logger.cpp"
 "Include/OstLog/Logging/LogLevel.h" "Include/OstLog/Logging/LogMessage.h" "Src/Internal/MessageQueue.h" "Src/Internal/MessageQueue.cpp" "Include/OstLog/Logging/ILogger.h" "Include/OstLog/Sinks/LogSink.h" "Src/LogSink.cpp" "Include/OstLog/MessageFormatter.h" "Src/MessageFormatter.cpp" "Include/OstLog/OstLogger.h"  "Include/OstLog/Logging/LoggingInstance.h" "Src/LoggingInstance.cpp" "Include/OstLog/Sinks/ConsoleLogSink.h" "Src/Sinks/ConsoleLogSink.cpp" "Include/OstLog/Sinks/FileLogSink.h" "Src/Sinks/FileLogSink.cpp" "Include/OstLog/CoreAPI.h" "Include/OstLog/APIDefinition.h" "Include/OstLog/Logging/LogScope.h" "Src/LogScope.cpp")

if(WIN32)
    target_compile_definitions(Logger PRIVATE "LOGGER_DLL_BUILD")
endif()

target_include_directories(Logger PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/Include"
    # Todo: Add third party sources
)

target_include_directories(Logger PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/Src"
)

set_target_properties(Logger PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
set_target_properties(Logger PROPERTIES OUTPUT_NAME "OstEngineLogging")

