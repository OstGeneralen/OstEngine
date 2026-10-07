cmake_minimum_required(VERSION 4.2)
project(OstGameProject)

add_library(${PROJECT_NAME} STATIC
    Game.h
    Game.cpp
    RotatingComponent.h
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${OSTENGINE_EXE_OUTPUT_DIR}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${OSTENGINE_EXE_OUTPUT_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE ${OST_ENGINE_NAME}
)
