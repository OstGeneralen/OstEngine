cmake_minimum_required(VERSION 4.2)
project(${OST_COMMON_NAME})

add_library(${PROJECT_NAME}
    STATIC
    Math/Vector2.h
    Math/Vector3.h
    Math/Math.h
    Math/Vector4.h
    Math/Quaternion.h
    Math/Matrix3x3.h
    Math/Matrix4x4.h
    Math/Color.h
    Memory/Memory.h
    Memory/Blob.h
    Utility/Assert.h
    Container/StackList.h
    Container/Queue.h
    Container/List.h
    Container/SlotMap.h
    Container/Map.h
    Container/SparseList.h
    Memory/UniquePtr.h
    Utility/TypeID.h
    Utility/File.h
    Utility/File.cpp
    Utility/Timer.h
    Utility/Timer.cpp
    Data/TextureCPUData.h
    Data/ModelCPUData.h
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${OSTENGINE_LIB_OUTPUT_DIR}
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${OSTENGINE_LIB_OUTPUT_DIR}
    DEBUG_POSTFIX "_debug"
    RELEASE_POSTFIX "_release"
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC DirectXMath
)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${OSTENGINE_INCLUDE_DIR}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    #PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
