cmake_minimum_required(VERSION 4.2)

add_executable(App
    Main.cpp
)

set_target_properties(App
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${OSTENGINE_EXE_OUTPUT_DIR}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${OSTENGINE_EXE_OUTPUT_DIR}
)

target_link_libraries(App
    PRIVATE OstEngine
)