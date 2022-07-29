//
// Created by chenxiaoyu5 on 2022/7/29.
//

#include "../common/include/raii.h"
#include "../common/include/fileraii.h"
#include "gtest/gtest.h"


TEST(raii, fileraii_test)
{
    CFileRaii cFileRaii("log", "log/test_log.txt");
    cFileRaii.write("hello world");
    cFileRaii.write("plog");
}


TEST(raii, commonraii_Test)
{
    std::ofstream file("log/test_log.txt");
    CRAIIManager file_raii([&file]()
       {
           if (file.is_open())  file.close();
       });
    file << "manager";
}
