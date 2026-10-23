cmake_minimum_required(VERSION 4.2)
project(OstEditor)

add_executable(${PROJECT_NAME}
    EditorApplication.cpp
    EditorContext.cpp
    EditorGameInstance.cpp
    EditorMain.cpp
    ImGui/imgui_demo.cpp
    ImGui/imgui_draw.cpp
    ImGui/imgui_tables.cpp
    ImGui/imgui_widgets.cpp
    ImGui/imgui_impl_dx11.cpp
    ImGui/imgui_impl_win32.cpp
    ImGui/imgui.cpp
    Content/stb_image.h
    Content/IconProvider.cpp
    System/SceneEditorContext.cpp
    GUI/PropertyEditor/PropertyEditorDrawer.cpp
    SceneView/SceneViewCamera.h
    SceneView/SceneViewCamera.cpp
    GUI/Layout/GUILayout.cpp
    GUI/Layout/GUIStackPanel.cpp
    GUI/EditorMasterGUI.cpp
    System/EditorCommandQueue.h
    System/EditorCommandQueue.cpp
    System/EditorCommand.h
    GUI/Layout/GUIContentContainer.h
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