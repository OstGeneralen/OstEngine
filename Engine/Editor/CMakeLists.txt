cmake_minimum_required(VERSION 4.2)
project(OstEditor)

add_executable(${PROJECT_NAME}
    EditorMain.cpp
    ImGui/imgui_demo.cpp
    ImGui/imgui_draw.cpp
    ImGui/imgui_tables.cpp
    ImGui/imgui_widgets.cpp
    ImGui/imgui_impl_dx11.cpp
    ImGui/imgui_impl_win32.cpp
    ImGui/imgui.cpp
    EditorApplication.h
    EditorApplication.cpp
    EditorGameInstance.h
    EditorGameInstance.cpp
    EditorContext.h
    EditorContext.cpp
    Panel/AssetsPanel.h
    Panel/EditorPanel.h
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