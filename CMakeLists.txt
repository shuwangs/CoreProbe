cmake_minimum_required(VERSION 3.16)
project(CoreProbe LANGUAGES CXX)

find_package(SDL3 CONFIG REQUIRED )

add_executable(coreprobe apps/coreprobe-cli/main.cpp)

# Link to the actual SDL3 library.
target_link_libraries(coreprobe PRIVATE SDL3::SDL3)

set_target_properties(coreprobe PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)
