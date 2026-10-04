cmake_minimum_required(VERSION 4.2)

add_library(OstEngine STATIC
    Debugging/Logger.h
    Debugging/Logger.cpp
    OstEngine.h
    OstEngine.cpp
    Asset/Asset.h
    Asset/AssetGuid.h
    Asset/ImageAsset.h
    Asset/ModelAsset.h
    Asset/Loaders/ImageLoader.h
    Asset/Loaders/ImageLoader.cpp
)

set_target_properties(OstEngine PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${OSTENGINE_LIB_OUTPUT_DIR}
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${OSTENGINE_LIB_OUTPUT_DIR}
)

target_include_directories(OstEngine
    PUBLIC ${OSTENGINE_INCLUDE_DIR}
)

target_link_libraries(OstEngine
    PUBLIC OstSTL
    PUBLIC OstGraphicsEngine
    PRIVATE DirectXTex
    PRIVATE assimp
)