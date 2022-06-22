cmake_minimum_required(VERSION 3.10)
project(server)

set(CMAKE_CXX_STANDARD 14)

include_directories(plugin)

add_executable(server main.cpp)
