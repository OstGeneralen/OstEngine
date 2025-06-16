add_library(Logger SHARED)

target_sources(Logger PRIVATE 
    "Src/Logger.cpp"
 "Include/OstLog/LogLevel.h" "Include/OstLog/LogMessage.h" "Src/Internal/MessageQueue.h" "Src/Internal/MessageQueue.cpp" "Include/OstLog/ILogger.h" "Include/OstLog/Sinks/LogSink.h" "Src/LogSink.cpp" "Include/OstLog/MessageFormatter.h" "Src/MessageFormatter.cpp" "Include/OstLog/OstLogger.h" "Include/OstLog/LoggerLifetimeManagement.h")

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

