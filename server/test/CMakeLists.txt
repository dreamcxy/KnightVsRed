add_executable(GServerTest main.cpp test_raii.cpp test_log.cpp)

set(CMAKE_CXX_FLAGS)

target_link_libraries(GServerTest ${GTEST_LIBRARY})
target_link_libraries(GServerTest pthread)
add_test(Test GServerTest)

ENABLE_TESTING()
