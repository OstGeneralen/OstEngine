cmake_minimum_required(VERSION 4.2)

add_library(OstEngine STATIC
    Debugging/Logger.h
    Debugging/Logger.cpp
    OstEngine.h
    OstEngine.cpp
    Asset/ImageAsset.h
    Asset/ImageAsset.cpp
)

set_target_properties(OstEngine PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${OSTENGINE_LIB_OUTPUT_DIR}
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${OSTENGINE_LIB_OUTPUT_DIR}
)

target_include_directories(OstEngine
    PUBLIC ${OSTENGINE_INCLUDE_DIR}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/Include
)



target_link_libraries(OstEngine
    PUBLIC OstSTL
    PUBLIC OstGraphicsEngine
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/Lib/assimp-vc143-mt.lib
)