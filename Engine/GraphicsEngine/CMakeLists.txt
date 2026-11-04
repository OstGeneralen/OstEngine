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
    Source/Objects/PipelineStateObject.h
    Source/Objects/PipelineStateObject.cpp
    Source/GraphicsEngine.cpp
    Source/GraphicsEngine.h
    Source/Rendering/RenderPipelineConstants.h
    Source/Rendering/RenderCommand.h
    Source/Resources/GraphicsResourceManager.h
    Source/Resources/GraphicsResourceManager.cpp
    Source/Rendering/Buffers.h
    Source/Resources/ShaderCompiler.h
    Source/Resources/ShaderCompiler.cpp
    Source/Rendering/ForwardRenderer.h
    Source/Rendering/ForwardRenderer.cpp
    Source/Rendering/RenderQueue.h
    Source/Rendering/RenderQueue.cpp
    Source/Materials/MaterialPropertyCollection.cpp
    Source/Materials/MaterialPropertyCollection.h
    Source/Materials/Material.h
    Source/Materials/MaterialInstance.h
    Source/Materials/Material.cpp
    Source/Materials/MaterialInstance.cpp
    Source/Materials/MaterialCompiler.h
    Source/Materials/MaterialCompiler.cpp
    Source/Materials/MaterialCompilerIncludeHandler.h
    Source/Materials/MaterialCompilerIncludeHandler.cpp
    Source/Objects/TextureSampler.cpp
    Source/Objects/TextureSampler.h
    Source/Materials/MaterialTextureCollection.cpp
    Source/Materials/MaterialUtility.h
    Source/Rendering/RenderCommandContext.h
    Source/Rendering/RenderCommand.cpp
    Source/Rendering/DeferredRenderer.h
    Source/Rendering/DeferredRenderer.cpp
    Source/Rendering/RendererContext.h
    Source/Objects/RenderDefaultsLibrary.h
    Source/Objects/RenderDefaultsLibrary.cpp
    Source/RHI/HLSLCompiler.cpp
    Source/Objects/Shader.h
    Source/Objects/Shader.cpp
    Source/Utility/ShaderReflector.cpp
    Source/Objects/Mesh.h
    Source/Objects/Mesh.cpp
    Source/Resources/Descriptors/PipelineStateDesc.cpp
    Source/Resources/Descriptors/ShaderDesc.cpp
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
