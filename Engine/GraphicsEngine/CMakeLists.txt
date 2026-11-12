cmake_minimum_required(VERSION 4.2)
project(${OST_GRAPHICS_ENGINE_NAME})

add_library(${PROJECT_NAME} STATIC
    Source/RHI/RenderHardwareInterface.h
    Source/RHI/RenderHardwareInterface.cpp
    Source/RHI/RHIMinimal.h
    Source/Objects/Texture.h
    Source/Objects/Texture.cpp
    Source/RHI/RHIInternal.h
    Source/Objects/Buffer.h
    Source/Objects/Buffer.cpp
    Source/GraphicsEngine.cpp
    Source/GraphicsEngine.h
    Source/Rendering/RenderPipelineConstants.h
    Source/Rendering/RenderCommand.h
    Source/Resources/GraphicsResourceManager.h
    Source/Resources/GraphicsResourceManager.cpp
    Source/Rendering/Buffers.h
    Source/Objects/TextureSampler.cpp
    Source/Objects/TextureSampler.h
    Source/Rendering/RenderCommand.cpp
    Source/Rendering/RendererContext.h
    Source/Objects/Shader.h
    Source/Objects/Shader.cpp
    Source/Utility/ShaderReflector.cpp
    Source/Resources/Descriptors/PipelineStateDesc.cpp
    Source/Resources/Descriptors/ShaderDesc.cpp
    Include/GraphicsEngine/Resources/Descriptors/BufferDesc.h
    Source/Resources/ShaderCompiler.cpp
    Include/GraphicsEngine/Rendering/IGraphicsScene.h
    Source/Rendering/GraphicsScene.h
    Source/Rendering/GraphicsScene.cpp
    Source/Rendering/SceneRenderer.h
    Source/Rendering/SceneRenderer.cpp
    Source/Rendering/RenderResourceLibrary.h
    Source/Rendering/RenderResourceLibrary.cpp
    Source/Rendering/PipelineState.h
    Source/Rendering/PipelineState.cpp
    Source/Objects/StateObjects.h
    Source/Objects/StateObjects.cpp
    Include/GraphicsEngine/Rendering/ISceneRenderer.h
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${OSTENGINE_LIB_OUTPUT_DIR}
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${OSTENGINE_LIB_OUTPUT_DIR}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Source
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE d3d11.lib
    PRIVATE dxgi.lib
    PRIVATE d3dcompiler.lib
    PRIVATE dxguid.lib
    PUBLIC ${OST_COMMON_NAME}
    PUBLIC ${OST_LOGGER_NAME}
)
