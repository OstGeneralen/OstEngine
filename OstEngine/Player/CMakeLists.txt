
add_executable(Player)

target_compile_definitions(Player PRIVATE "GAME_MODULE_DLL_NAME=\"${GAME_MODULE_NAME}.dll\"")

target_sources(Player PRIVATE "Src/Main.cpp")

target_link_libraries(Player PRIVATE Engine)

target_include_directories(Engine PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/Include"
    # Todo: Add third party sources
)

set_target_properties(Player PROPERTIES OUTPUT_NAME "${GAME_NAME}")