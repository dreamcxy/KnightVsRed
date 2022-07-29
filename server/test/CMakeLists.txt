add_executable(GServerTest test.cpp test_raii.cpp)


target_link_libraries(GServerTest ${GTEST_LIBRARY})
target_link_libraries(GServerTest pthread)
add_test(Test GServerTest)

ENABLE_TESTING()
