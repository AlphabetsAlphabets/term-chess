cmake_minimum_required(VERSION 3.24)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS True)
set(CMAKE_CXX_STANDARD, 20)
set(CMAKE_CXX_STANDARD_REQUIRED, True)

project(chess)
add_executable(chess main.cpp)
