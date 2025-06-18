# PROJECT
# ======================================================================
# Sources
add_library(Engine STATIC 
    "Src/Game/GameModuleInternal.cpp"
    
    "Src/Application/Config/CmdArgs.cpp" 
     
    "Src/Engine.cpp" 
    
       
    "Src/Application/Config/Configurations.cpp" 
    "Src/Application/Config/ConfigFile.cpp"
    "Src/Subsystem/Input/InputSystem.cpp" 
    "Src/Application/Application.cpp" 
    "Src/Subsystem/Assets/AssetsSystem.cpp" 
    "Src/Utility/PathUtils.cpp"   
    "Src/Application/Window/AppWindow.cpp" 
    "Src/Rendering/TextureRenderTarget.cpp" 
    "Src/Subsystem/Input/InputEventProvider.cpp"
)

target_include_directories(Engine PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Src" )       # Internal includes
target_include_directories(Engine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Include" )    # Interface includes
target_link_libraries(Engine PRIVATE Logger)
# ======================================================================

# THIRD PARTY
# ======================================================================
# Sources
target_sources(Engine PRIVATE 
    # ... Glad .........................................................    
    "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/OpenGL/Src/glad.c"

    # ... ImGui ........................................................
    "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/ImGui/Src/imgui.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/ImGui/Src/imgui_demo.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/ImGui/Src/imgui_draw.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/ImGui/Src/imgui_impl_glfw.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/ImGui/Src/imgui_impl_opengl3.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/ImGui/Src/imgui_tables.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/ImGui/Src/imgui_widgets.cpp"
)

# Headers
target_include_directories(Engine PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/OpenGL/Include"
    "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/ImGui/Include"
)
# ======================================================================

# LINKING
# ======================================================================
target_link_libraries(Engine PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/OpenGL/Lib/glfw3.lib"
    "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/OpenGL/Lib/OpenGL32.lib"
)
# ======================================================================

# CONFIGS
# ======================================================================
if(WIN_BUILD)
target_compile_definitions(Engine PRIVATE "APP_WIN32")
endif()
# ======================================================================