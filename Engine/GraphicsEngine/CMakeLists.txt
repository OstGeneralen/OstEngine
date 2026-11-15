cmake_minimum_required(VERSION 4.2)
project(${OST_GRAPHICS_ENGINE_NAME})

add_library(${PROJECT_NAME} STATIC
    Source/RHI/RenderHardwareInterface.h
    Source/RHI/RenderHardwareInterface.cpp
    Source/RHI/RHIMinimal.h
    Source/RHI/RHIInternal.h
    Source/GraphicsEngine.cpp
    Source/GraphicsEngine.h
    Source/Rendering/RenderPipelineConstants.h
    Source/Rendering/RenderCommand.h
    Source/Rendering/Buffers.h
    Source/Objects/TextureSampler.cpp
    Source/Objects/TextureSampler.h
    Source/Rendering/RenderCommand.cpp
    Source/Rendering/RendererContext.h
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
    Source/Resources/PipelineStateCache.h
    Include/GraphicsEngine/Resources/IGraphicsResource.h
    Include/GraphicsEngine/Resources/Shaders.h
    Include/GraphicsEngine/Resources/Buffers.h
    Include/GraphicsEngine/Resources/Textures.h
    Source/Resources/GfxBuffers.h
    Source/Resources/GfxShaders.h
    Source/Resources/GfxTextures.h
    Source/Resources/GfxResourceHelper.h
    Source/RHI/RHIResourceFactory.h
    Source/Resources/GfxTextures.cpp
    Source/Resources/GfxShaders.cpp
    Source/Resources/GfxBuffers.cpp
    Include/GraphicsEngine/Resources/Managers/IGfxTextureManager.h
    Include/GraphicsEngine/Resources/Managers/IGfxBufferManager.h
    Include/GraphicsEngine/Resources/Managers/IGfxResourceManager.h
    Include/GraphicsEngine/Resources/Managers/IGfxShaderManager.h
    Include/GraphicsEngine/Resources/Descriptors/ShaderStub.h
    Source/Resources/Managers/GfxBufferManager.h
    Source/Resources/Managers/GfxShaderManager.h
    Source/Resources/Managers/GfxTextureManager.h
    Source/Resources/Managers/GfxResourceManager.h
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
