cmake_minimum_required(VERSION 4.2)
project(OstEngine)

# ===================================================================================

set(OSTENGINE_EXE_OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Bin)
set(OSTENGINE_DLL_OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Bin)
set(OSTENGINE_LIB_OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Artefacts/Lib)
set(OSTENGINE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Source)

# ===================================================================================

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

# ===================================================================================

add_subdirectory(Dependencies/DirectXMath)

set(DIRECTXMATH_HEADER_ONLY ON CACHE BOOL "" FORCE)

add_subdirectory(Dependencies/DirectXTex)
set_target_properties(DirectXTex PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${OSTENGINE_LIB_OUTPUT_DIR} ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${OSTENGINE_LIB_OUTPUT_DIR} DEBUG_POSTFIX "_d")      

add_subdirectory(Dependencies/Assimp)
set_target_properties(assimp PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${OSTENGINE_LIB_OUTPUT_DIR} ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${OSTENGINE_LIB_OUTPUT_DIR} DEBUG_POSTFIX "_d" LIBRARY_OUTPUT_DIRECTORY_DEBUG ${OSTENGINE_DLL_OUTPUT_DIR} LIBRARY_OUTPUT_DIRECTORY_RELEASE ${OSTENGINE_DLL_OUTPUT_DIR})      



add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Source/Common)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Source/GraphicsEngine)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Source/Engine)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Source/Application)