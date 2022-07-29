add_executable(GServerTest test.cpp test_raii.cpp)

add_test(Test GServerTest)

ENABLE_TESTING()