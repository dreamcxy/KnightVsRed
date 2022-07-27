cmake_minimum_required(VERSION 3.00)
project(server)

set(CMAKE_CXX_STANDARD 14)

include_directories(plugin)

#编译器
set(CMAKE_C_COMPILER, "clang")
set(CMAKE_CXX_COMPILER, "clang++")

#库文件
set(CMAKE_CXX_FLAGS -lpthread)

add_executable(server main.cpp common/include/fileraii.h common/include/raii.h)
