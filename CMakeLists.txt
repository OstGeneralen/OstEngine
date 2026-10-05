cmake_minimum_required(VERSION 4.2)
project(OstEngine)

# ===================================================================================

set(OSTENGINE_EXE_OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Bin)
set(OSTENGINE_DLL_OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Bin)
set(OSTENGINE_LIB_OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Artefacts/Lib)
set(OSTENGINE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Engine)

set(OST_COMMON_NAME OstCommon)
set(OST_LOGGER_NAME OstLogger)
set(OST_ENGINE_NAME OstEngine)
set(OST_GRAPHICS_ENGINE_NAME OstGraphicsEngine)

# ===================================================================================

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

# ===================================================================================
# Define helper functions

function(OstAddSubdirEnsureCompliant moduleSubdir subdirName)
    add_subdirectory(${moduleSubdir})

    set_target_properties( ${subdirName} PROPERTIES 
        ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${OST_ENGINE_LIB_OUTPUT_DIR}
        ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${OST_ENGINE_LIB_OUTPUT_DIR}
        LIBRARY_OUTPUT_DIRECTORY_DEBUG ${OSTENGINE_DLL_OUTPUT_DIR}
        LIBRARY_OUTPUT_DIRECTORY_RELEASE ${OSTENGINE_DLL_OUTPUT_DIR}
        DEBUG_POSTFIX "_d"
    )
endfunction()

function(OstForceSetOption optionName toggle)
    set(${optionName} ${toggle} CACHE BOOL "" FORCE)
endfunction()

# ===================================================================================
# Overridden configuration options

# DirectXMath
OstForceSetOption(DIRECTXMATH_HEADER_ONLY ON)   # Required to be ON, else DirectXMath and DirectXTex starts conflicting on the Math lib use

# Assimp
OstForceSetOption(ASSIMP_BUILD_TESTS OFF)       # Kinda assume this is indeed tested so let's not bother building the tests for ourselves
OstForceSetOption(ASSIMP_INSTALL OFF)           # Don't install, let's keep it small

# ===================================================================================
# Add Subdirectories

# Dependencies
OstAddSubdirEnsureCompliant(Dependencies/DirectXMath DirectXMath)
OstAddSubdirEnsureCompliant(Dependencies/DirectXTex DirectXTex)
OstAddSubdirEnsureCompliant(Dependencies/Assimp assimp)

# Our packages
OstAddSubdirEnsureCompliant(Shared/OstUtilities ${OST_COMMON_NAME})
OstAddSubdirEnsureCompliant(Shared/OstLogger ${OST_LOGGER_NAME})
OstAddSubdirEnsureCompliant(Engine/GraphicsEngine ${OST_GRAPHICS_ENGINE_NAME})
OstAddSubdirEnsureCompliant(Engine/Engine ${OST_ENGINE_NAME})
OstAddSubdirEnsureCompliant(Game App)