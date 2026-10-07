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
    Game/Scene.h
    Game/Actor.h
    Game/Component.h
    Game/Transform.h
    Game/Actor.cpp
    Game/Scene.cpp
    Game/Components/StaticMeshComponent.h
    Game/Components/CameraComponent.h
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
