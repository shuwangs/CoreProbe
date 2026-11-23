cmake_minimum_required(VERSION 3.16)
project(CoreProbe LANGUAGES CXX)

add_executable(coreprobe apps/coreprobe-cli/main.cpp)
set_target_properties(coreprobe PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)
