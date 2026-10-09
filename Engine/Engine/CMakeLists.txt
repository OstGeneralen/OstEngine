cmake_minimum_required(VERSION 4.2)
project(${OST_ENGINE_NAME})

add_library(${PROJECT_NAME} STATIC
    Include/Engine/Asset/Asset.h
    Include/Engine/Asset/AssetGuid.h
    Include/Engine/Asset/IAssetManager.h
    Include/Engine/Components/CameraComponent.h
    Include/Engine/Components/SceneLightComponent.h
    Include/Engine/Components/StaticMeshComponent.h
    Include/Engine/Game/GameInterface.h
    Include/Engine/World/Actor.h
    Include/Engine/World/Component.h
    Include/Engine/World/ComponentContext.h
    Include/Engine/World/IComponentInitializer.h
    Include/Engine/World/Scene.h
    Include/Engine/World/SceneGraph.h
    Include/Engine/World/Transform.h
    Include/Engine/World/WorldContext.h
    Include/Engine/EngineContext.h
    Include/Engine/IOstEngine.h
    Include/Engine/System/InputReader.h
    Source/Asset/Loaders/ImageLoader.cpp
    Source/Asset/Loaders/ImageLoader.h
    Source/Asset/Loaders/ModelLoader.cpp
    Source/Asset/Loaders/ModelLoader.h
    Source/Asset/AssetManager.h
    Source/Asset/AssetManager.cpp
    Source/Components/CameraComponent.cpp
    Source/Components/SceneLightComponent.cpp
    Source/Components/StaticMeshComponent.cpp
    Source/World/Actor.cpp
    Source/World/Component.cpp
    Source/World/ComponentInitializer.cpp
    Source/World/ComponentInitializer.h
    Source/World/ComponentTicker.cpp
    Source/World/ComponentTicker.h
    Source/World/GameWorld.cpp
    Source/World/GameWorld.h
    Source/World/Scene.cpp
    Source/World/SceneGraph.cpp
    Source/System/InputReader.cpp
    Source/OstEngine.cpp
    Source/OstEngine.h
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${OSTENGINE_LIB_OUTPUT_DIR}
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${OSTENGINE_LIB_OUTPUT_DIR}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Source
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Inclue/Engine
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC ${OST_COMMON_NAME}
    PUBLIC ${OST_LOGGER_NAME}
    PUBLIC ${OST_GRAPHICS_ENGINE_NAME}
    PRIVATE DirectXTex
    PRIVATE assimp
)
