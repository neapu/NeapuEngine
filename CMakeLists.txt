cmake_minimum_required(VERSION 3.15)
project(NeapuEngine CXX)
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    add_compile_options("/utf-8")
endif()
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_subdirectory(engine)
add_subdirectory(exec)