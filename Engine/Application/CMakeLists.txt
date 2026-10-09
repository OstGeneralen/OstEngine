cmake_minimum_required(VERSION 4.2)
project( OstEngineApplication )

add_executable(${PROJECT_NAME}
    Main.cpp
    Application.h
    Application.cpp
    Platform/Platform.h
    Platform/PlatformWin32.cpp
    CoutLogSink.h
    CoutLogSink.cpp
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE 
        ${OST_ENGINE_NAME}
        ${OST_GRAPHICS_ENGINE_NAME}
        ${GAME_PROJECT_NAME}
)

target_include_directories(${PROJECT_NAME}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)