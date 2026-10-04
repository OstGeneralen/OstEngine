cmake_minimum_required(VERSION 4.2)

add_library(OstGraphicsEngine STATIC
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
    Objects/Material.h
    Rendering/Vertex.h
    Objects/Material.cpp
    Rendering/RenderPipelineConstants.h
    Objects/ObjectHandles.h
    Rendering/RenderCommand.h
    Resources/MaterialFactory.h
    Resources/MaterialFactory.cpp
    Resources/IGraphicsResourceManager.h
    Resources/GraphicsResourceManager.h
    Resources/GraphicsResourceManager.cpp
)

set_target_properties(OstGraphicsEngine PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${OSTENGINE_LIB_OUTPUT_DIR}
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${OSTENGINE_LIB_OUTPUT_DIR}
)

target_include_directories(OstGraphicsEngine
    PUBLIC ${OSTENGINE_INCLUDE_DIR}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(OstGraphicsEngine
    PUBLIC d3d11.lib
    PUBLIC dxgi.lib
    PRIVATE d3dcompiler.lib
    PUBLIC OstSTL
)