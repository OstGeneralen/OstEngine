cmake_minimum_required(VERSION 4.2)
project(${OST_GRAPHICS_ENGINE_NAME})

add_library(${PROJECT_NAME} STATIC
    RHI/RenderHardwareInterface.h
    RHI/RenderHardwareInterface.cpp
    RHI/RHIMinimal.h
    Objects/Texture.h
    Objects/Texture.cpp
    RHI/RHIInternal.h
    Objects/Buffer.h
    Objects/Buffer.cpp
    Objects/PipelineStateObject.h
    Objects/PipelineStateObject.cpp
    GraphicsEngine.h
    GraphicsEngine.cpp
    GraphicsEngineSettings.h
    Objects/Model.h
    Rendering/Vertex.h
    Rendering/RenderPipelineConstants.h
    Objects/ObjectHandles.h
    Rendering/RenderCommand.h
    Resources/IGraphicsResourceManager.h
    Resources/GraphicsResourceManager.h
    Resources/GraphicsResourceManager.cpp
    Rendering/Buffers.h
    Resources/ShaderCompiler.h
    Resources/ShaderCompiler.cpp
    Rendering/IRenderer.h
    Rendering/Light.h
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${OSTENGINE_LIB_OUTPUT_DIR}
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${OSTENGINE_LIB_OUTPUT_DIR}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${OSTENGINE_INCLUDE_DIR}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC d3d11.lib
    PUBLIC dxgi.lib
    PRIVATE d3dcompiler.lib
    PUBLIC ${OST_COMMON_NAME}
    PUBLIC ${OST_LOGGER_NAME}
)
