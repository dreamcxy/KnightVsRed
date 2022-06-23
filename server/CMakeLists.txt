cmake_minimum_required(VERSION 3.10)
project(server)

set(CMAKE_CXX_STANDARD 14)

include_directories(plugin)

#库文件
set(CMAKE_CXX_FLAGS -lpthread)

add_executable(server main.cpp)
