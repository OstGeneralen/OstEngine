add_library(Engine STATIC)

file(GLOB_RECURSE ENGINE_SOURCES "Src/*.cpp")
target_sources(Engine PRIVATE ${ENGINE_SOURCES})

target_include_directories(Engine PUBLIC 
    "${CMAKE_CURRENT_SOURCE_DIR}/Include"
    # Todo: Add third party sources
)