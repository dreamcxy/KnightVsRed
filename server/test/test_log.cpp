//
// Created by chenxiaoyu5 on 2022/7/29.
//

#include "include/logger.h"
#include "gtest/gtest.h"
#include "iostream"
#include "commondefine.h"

using namespace std;



TEST(log, test_log)
{
    std::unique_ptr<CharLogBuffer> pstBuffer(new CharLogBuffer(1024));
    std::unique_ptr<FileHandler<CharLogBuffer>> pstHandler(new FileHandler<CharLogBuffer>(E_LOG_LEVEL::E_INFO));
    std::unique_ptr<SLog<FileHandler<CharLogBuffer>>> pstLog(new SLog<FileHandler<CharLogBuffer>>());

    cout << &pstLog << endl;

}

TEST(log, test_magic_enum)
{
    std::cout << E_LOG_LEVELToString(E_LOG_LEVEL::E_INFO);

}