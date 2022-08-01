//
// Created by chenxiaoyu5 on 2022/7/29.
//

#include "include/logger.h"
#include "gtest/gtest.h"
#include "iostream"

using namespace std;

template<typename E, E v>
void f()
{
    cout << __PRETTY_FUNCTION__  << endl;
}

TEST(log, test_log)
{
    std::unique_ptr<CharLogBuffer> pstBuffer(new CharLogBuffer(1024));
    std::unique_ptr<FileHandler<CharLogBuffer>> pstHandler(new FileHandler<CharLogBuffer>(INFO));
    std::unique_ptr<SLog<FileHandler<CharLogBuffer>>> pstLog(new SLog<FileHandler<CharLogBuffer>>());

    cout << &pstLog << endl;

}

TEST(log, test_magic_enum)
{
    constexpr E_LOG_LEVEL logLevel = E_LOG_LEVEL::INFO;

    f<E_LOG_LEVEL, logLevel>();
    
}