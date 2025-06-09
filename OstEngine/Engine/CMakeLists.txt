add_library(Engine STATIC 
    "Src/Application/Config/CommandLineParser.cpp"
    "Src/Application/Config/ConfigFileParser.cpp"
    "Src/Game/GameModuleInternal.cpp"
 "Src/Application/Window/Window.cpp")

if(WIN_BUILD)
target_compile_definitions(Engine PRIVATE "APP_WIN32")
endif()

target_include_directories(Engine PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/Include"
    # Todo: Add third party sources
)