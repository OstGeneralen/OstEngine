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

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Source/Common)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Source/GraphicsEngine)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Source/Engine)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Source/Application)