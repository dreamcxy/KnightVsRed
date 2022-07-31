//
// Created by chenxiaoyu5 on 2022/7/29.
//

#include "include/logger.h"
#include "gtest/gtest.h"
#include "iostream"

using namespace std;

TEST(log, test_log)
{
    std::unique_ptr<CharLogBuffer> pstBuffer(new CharLogBuffer(1024));
    std::unique_ptr<FileHandler<CharLogBuffer>> pstHandler(new FileHandler<CharLogBuffer>(LOG_LEVEL_INFO));
    std::unique_ptr<SLog<FileHandler<CharLogBuffer>>> pstLog(new SLog<FileHandler<CharLogBuffer>>());

    cout << &pstLog << endl;

}