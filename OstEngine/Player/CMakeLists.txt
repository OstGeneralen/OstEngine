
add_executable(Player)

target_compile_definitions(Player PRIVATE "GAME_MODULE_DLL_NAME=\"${GAME_MODULE_NAME}.dll\"")

target_sources(Player PRIVATE "Src/Main.cpp"  )

target_link_libraries(Player PRIVATE Engine)
target_link_libraries(Player PRIVATE Logger)

target_include_directories(Player PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/Src"
    # Todo: Add third party sources
)

set_target_properties(Player PROPERTIES OUTPUT_NAME "${GAME_NAME}")