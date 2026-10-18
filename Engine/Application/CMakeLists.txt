cmake_minimum_required(VERSION 4.2)
project( OstEngineApplication )

add_executable(${PROJECT_NAME}
    Main.cpp
    Application.h
    Application.cpp
    CoutLogSink.h
    CoutLogSink.cpp
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE 
        ${OST_ENGINE_NAME}
        ${OST_GRAPHICS_ENGINE_NAME}
        ${GAME_PROJECT_NAME}
        nlohmann_json
)

target_include_directories(${PROJECT_NAME}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)