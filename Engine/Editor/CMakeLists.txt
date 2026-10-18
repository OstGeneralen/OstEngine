cmake_minimum_required(VERSION 4.2)
project(OstEditor)

add_executable(${PROJECT_NAME}
    EditorMain.cpp
    ImGui/imgui_demo.cpp
    ImGui/imgui_draw.cpp
    ImGui/imgui_tables.cpp
    ImGui/imgui_widgets.cpp
    ImGui/imgui.cpp
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        OstGameProject
        OstEngine
        OstGraphicsEngine
        nlohmann_json
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/ImGui
)