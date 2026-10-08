cmake_minimum_required(VERSION 4.2)
project(${OST_ENGINE_NAME})


add_library(${PROJECT_NAME} STATIC
    OstEngine.h
    OstEngine.cpp
    Asset/Asset.h
    Asset/AssetGuid.h
    Asset/ImageAsset.h
    Asset/ModelAsset.h
    Asset/Loaders/ImageLoader.h
    Asset/Loaders/ImageLoader.cpp
    Asset/Loaders/ModelLoader.h
    Asset/Loaders/ModelLoader.cpp
    Game/GameInterface.h
    Asset/GraphicsAssetsManager.h
    Asset/GraphicsAssetsManager.cpp
    Game/Transform.h
    EngineContext.h
    System/InputReader.h
    System/InputReader.cpp
    World/Component.h
    World/RenderGraph.h
    World/ComponentInitializer.h
    World/Component.cpp
    Components/StaticMeshComponent.h
    Components/StaticMeshComponent.cpp
    World/RenderGraph.cpp
    World/ComponentInitializer.cpp
    World/ComponentTicker.h
    World/IComponentTicker.h
    World/ComponentTicker.cpp
    World/ComponentContext.h
    World/GameWorld.h
    World/GameWorld.cpp
    Components/CameraComponent.h
    Components/CameraComponent.cpp
    World/Actor.h
    World/WorldContext.h
    World/Actor.cpp
    World/Scene.h
    World/Scene.cpp
    Components/SceneLightComponent.h
    Components/SceneLightComponent.cpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${OSTENGINE_LIB_OUTPUT_DIR}
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${OSTENGINE_LIB_OUTPUT_DIR}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${OSTENGINE_INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC ${OST_COMMON_NAME}
    PUBLIC ${OST_LOGGER_NAME}
    PUBLIC ${OST_GRAPHICS_ENGINE_NAME}
    PRIVATE DirectXTex
    PRIVATE assimp
)
