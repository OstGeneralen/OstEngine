cmake_minimum_required(VERSION 4.2)

add_library(OstSTL
    INTERFACE
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
)

set_target_properties(OstSTL PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${OSTENGINE_LIB_OUTPUT_DIR}
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${OSTENGINE_LIB_OUTPUT_DIR}
    DEBUG_POSTFIX "_debug"
    RELEASE_POSTFIX "_release"
)

target_include_directories(OstSTL
    INTERFACE ${OSTENGINE_INCLUDE_DIR}
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty
    #PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)
