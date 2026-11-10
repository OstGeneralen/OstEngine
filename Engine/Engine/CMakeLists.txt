cmake_minimum_required(VERSION 4.2)
project(${OST_ENGINE_NAME})

add_library(${PROJECT_NAME} STATIC
    Source/OstEngine.cpp
    Source/Asset/AssetManager.cpp
    Source/Components/CameraComponent.cpp
    Source/Components/StaticMeshComponent.cpp
    Source/Components/LightComponent.cpp
    Source/Components/PointLightComponent.cpp
    Source/Components/SpotLightComponent.cpp
    Source/World/Actor.cpp
    Source/World/Component.cpp
    Source/World/ComponentInitializer.cpp
    Source/World/ComponentTicker.cpp
    Source/World/Scene.cpp
    Source/World/SceneGraph.cpp
    Source/World/SceneManager.cpp
    Source/World/ComponentFactory.cpp
    Source/System/InputReader.cpp
    Source/System/TimeProvider.cpp
    Source/Components/DirectionalLightComponent.cpp
    Source/Configuration/RuntimeConfig.cpp
    Source/Platform/Win32Window.cpp
    Source/Asset/DefaultAssets.cpp
    Source/Asset/Asset.cpp
    Source/Asset/AssetRef.cpp
    Include/Engine/Asset/AssetFactory.h
    Source/Asset/Loaders/TextureFactory.cpp
    Source/Asset/Loaders/ModelFactory.cpp
    Source/Asset/Loaders/ShaderFactory.cpp
    Source/Graphics/Material/MaterialClass.cpp
    Source/Graphics/Material/MaterialInstance.cpp
    Source/Graphics/Material/MaterialPropertySet.cpp
    Source/Graphics/Material/MaterialProperty.cpp
    Source/Graphics/Material/MaterialManager.cpp
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
    PRIVATE nlohmann_json
    PRIVATE DirectXTex
    PRIVATE assimp
)
