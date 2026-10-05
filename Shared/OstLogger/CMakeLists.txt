cmake_minimum_required(VERSION 4.2)
project(${OST_LOGGER_NAME})

add_library(${PROJECT_NAME} STATIC
    Include/OstLog.h
    Include/OstLogMessage.h
    Include/OstLogSink.h
    Src/OstLogLogger.cpp
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC ${OST_COMMON_NAME}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Src
)