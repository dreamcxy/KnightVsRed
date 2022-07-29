cmake_minimum_required(VERSION 3.00)
project(server)

set(CMAKE_CXX_STANDARD 14)

include_directories(plugin)
include_directories(test)

#gtest
find_package(GTest REQUIRED)
if (GTest_FOUND)
    include_directories(${GTEST_INCLUDE_DIR})
endif ()

#编译器
set(CMAKE_C_COMPILER, "clang")
set(CMAKE_CXX_COMPILER, "clang++")

#库文件
#set(CMAKE_CXX_FLAGS -lgtest -lgtest_main)
#set(CMAKE_CXX_FLAGS -lpthread)

list(APPEND COMMON_LIB -lgtest -lgtest_main -lpthread)



add_executable(server main.cpp common/include/fileraii.h common/include/raii.h)

add_executable(GServerTest test/test.cpp test/test_raii.cpp)

target_link_libraries(GServerTest ${GTEST_LIBRARY})

add_test(Test GServerTest)
ENABLE_TESTING()
