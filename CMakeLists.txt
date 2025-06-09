cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(OstEngineWorkspace)

# ============================================================
#						CONFIGURATION
# ============================================================
set(EDITOR_BUILD OFF CACHE BOOL "Editor exe instead of game")
set(WIN_BUILD ON CACHE BOOL "Use WinMain instead of main")
set(GAME_NAME "Game" CACHE STRING "Name of the game")
# ============================================================

set(GAME_MODULE_NAME "${GAME_NAME}_GameModule" CACHE STRING "Name of the game module")
set(GAME_DLL_NAME "${GAME_MODULE_NAME}.dll" CACHE STRING "Name of the dll of the game")


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_subdirectory(OstEngine/Engine)
add_subdirectory(${GAME_NAME})

if(EDITOR_BUILD)
add_subdirectory(OstEngine/Editor)
else()
add_subdirectory(OstEngine/Player)
endif()