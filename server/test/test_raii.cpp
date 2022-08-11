//
// Created by cxy on 2022/7/29.
//

#include "raii.h"
#include "fileraii.h"
#include "gametime.h"
#include "gtest/gtest.h"
#include <iostream>

using namespace std;

TEST(raii, fileraii_test)
{
    CFileRaii cFileRaii("log", "log/fileraii_log.txt");
    cFileRaii.write("hello world");
    cFileRaii.write("plog");
}


TEST(raii, commonraii_Test)
{
    std::ofstream file("log/commonraii_log.txt");
    CRAIIManager file_raii([&file]()
       {
           if (file.is_open())  file.close();
       });
    file << "manager";
}

TEST(raii, test_instance)
{
    CGameTime* poGameTime = CGameTime::GetInstance();
    cout << poGameTime->GetCurSecond() << endl;
}