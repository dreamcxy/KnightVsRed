# gtest的配置

- git clone https://github.com/google/googletest.git

- gcc 和 clang版本都要大于5.0 

- CMakeLists.txt 里面注明是用c++ 14 

- 直接在googtest目录下面make install即可，.a 文件会安装到/usr/local/lib

- server的cmakelist里面要注明-lgtest, 要放在lpthread前面

  ``

  ```
  add_executable(GServerTest main.cpp test_raii.cpp test_log.cpp)
  
  set(CMAKE_CXX_FLAGS)
  // 链接library
  target_link_libraries(GServerTest ${GTEST_LIBRARY})
  target_link_libraries(GServerTest pthread)
  add_test(Test GServerTest)
  
  ENABLE_TESTING()
  ```