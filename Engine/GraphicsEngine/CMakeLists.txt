cmake_minimum_required(VERSION 4.2)
project(${OST_GRAPHICS_ENGINE_NAME})

add_library(${PROJECT_NAME} STATIC
    Include/GraphicsEngine/Rendering/Vertex.h
    Include/GraphicsEngine/Rendering/IRenderer.h
    Include/GraphicsEngine/Resources/ObjectHandles.h
    Include/GraphicsEngine/Resources/TextureCPUData.h
    Include/GraphicsEngine/Resources/ModelCPUData.h
    Include/GraphicsEngine/Resources/IGraphicsResourceManager.h
    Include/GraphicsEngine/Rendering/IRenderQueue.h
    Include/GraphicsEngine/IGraphicsEngine.h
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
    Source/Objects/Model.h
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
    Include/GraphicsEngine/Materials/IMaterial.h
    Include/GraphicsEngine/Materials/IMaterialPropertyCollection.h
    Include/GraphicsEngine/Materials/MaterialConstants.h
    Include/GraphicsEngine/Materials/MaterialPropertyTypes.h
    Source/Materials/MaterialPropertyCollection.cpp
    Source/Materials/MaterialPropertyCollection.h
    Include/GraphicsEngine/Materials/IMaterialInstance.h
    Include/GraphicsEngine/Materials/IMaterialManager.h
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
    Include/GraphicsEngine/Materials/MaterialTextureCollection.h
    Source/Materials/MaterialTextureCollection.cpp
    Source/Materials/MaterialUtility.h
    Source/Rendering/RenderCommandContext.h
    Source/Rendering/RenderCommand.cpp
    Include/GraphicsEngine/IRenderHardwareInterface.h
    Source/Rendering/DeferredRenderer.h
    Source/Rendering/DeferredRenderer.cpp
    Source/Rendering/RendererContext.h
    Include/GraphicsEngine/Rendering/RenderConstants.h
    Include/GraphicsEngine/Rendering/Lights.h
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
