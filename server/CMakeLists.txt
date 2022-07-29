cmake_minimum_required(VERSION 3.00)
project(KnightVsRedServer)

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

# 需要编译的可执行模块
list(APPEND EXE_MODULES test)

# 设定输出位置
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${PROJECT_SOURCE_DIR}/bin)

# 包含通用头文件
include_directories("common" "common/include")

# 库文件
#list(APPEND COMMON_LIB common)
list(APPEND COMMON_LIB -lgtest  -lpthread)


foreach(EXE ${EXE_MODULES})
    add_subdirectory(${EXE})
endforeach()

