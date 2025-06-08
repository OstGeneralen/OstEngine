add_library(${GAME_NAME} SHARED)

file(GLOB_RECURSE GAME_SOURCES "Src/*.cpp")
target_sources(${GAME_NAME} PRIVATE ${GAME_SOURCES})

target_link_libraries(${GAME_NAME} PRIVATE Engine)

if(WIN32)
    string(TOUPPER ${GAME_NAME} UPPER_GAME_NAME)
    target_compile_definitions(${GAME_NAME} PRIVATE "${UPPER_GAME_NAME}_DLL_BUILD")
endif()

target_include_directories(${GAME_NAME} PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/Include"
    # Todo: Add third party sources
)

set_target_properties(${GAME_NAME} PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
set_target_properties(${GAME_NAME} PROPERTIES OUTPUT_NAME "${GAME_MODULE_NAME}")

