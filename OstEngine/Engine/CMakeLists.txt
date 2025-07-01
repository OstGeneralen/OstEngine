# PROJECT
# ======================================================================
# Sources
add_library(Engine STATIC 
    "Src/Engine.cpp" 
    "Src/Game/GameModuleInternal.cpp"
    
    "Src/Application/Application.cpp" 
    "Src/Application/Config/CmdArgs.cpp" 
    "Src/Application/Config/Configurations.cpp" 
    "Src/Application/Config/ConfigFile.cpp"
    "Src/Application/Window/AppWindow.cpp" 
     
    "Src/Rendering/TextureRenderTarget.cpp" 
    
    "Src/Subsystem/Assets/AssetsSystem.cpp" 
    "Src/Subsystem/Input/InputSystem.cpp" 
    "Src/Subsystem/Input/InputEventProvider.cpp"
    
    "Src/Utility/PathUtils.cpp"   
    
    # MATH
    "Src/Math/CommonMath.cpp" 
    "Src/Math/Units/Radians.cpp" 
    "Src/Math/Units/Degrees.cpp" 
    "Include/OstEngine/BasicTypes.h"
    "Include/OstEngine/Math/Structures/Mat4x4.h" 
    "Include/OstEngine/Math/Structures/Mat3x3.h"
    "Include/OstEngine/Math/Structures/Quaternion.h"
    "Src/Math/Transform.cpp"
    "Include/OstEngine/Math/Transform.h"
    
    # OBJECT SYSTYEM
    "Include/OstEngine/ObjectSystem/StableIndexedType.h"
    "Include/OstEngine/ObjectSystem/Internal/StableIndex.h" 
    "Include/OstEngine/ObjectSystem/Internal/StableIndexedTypeContainer.h"
    "Include/OstEngine/ObjectSystem/Internal/StableIndexedTypeContainerBase.h"
    "Include/OstEngine/ObjectSystem/Internal/ComponentContainer.h" 
    "Include/OstEngine/ObjectSystem/Internal/ComponentRegistry.h" 
    "Include/OstEngine/ObjectSystem/ObjectSystem.h" 
    "Include/OstEngine/ObjectSystem/Component/Component.h" 
    "Include/OstEngine/ObjectSystem/Component/ComponentsCore.h" 
    "Include/OstEngine/ObjectSystem/Component/ComponentHandle.h" 
    "Include/OstEngine/ObjectSystem/Objects/GameObjectHandle.h" 
    "Src/ObjectSystem/Internal/StableIndexedTypeContainerBase.cpp"
    "Src/ObjectSystem/Internal/ComponentRegistry.cpp" 
    "Src/ObjectSystem/ObjectSystem.cpp"   
    "Src/ObjectSystem/Objects/GameObjectHandle.cpp" 
    "Src/ObjectSystem/Component/ComponentHandle.cpp" 
    "Src/ObjectSystem/Objects/GameObject.cpp" 
    "Src/ObjectSystem/Component/Component.cpp"   
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