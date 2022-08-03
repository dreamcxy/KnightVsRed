//
// Created by chenxiaoyu5 on 2022/7/29.
//


#include "logger.h"
#include "gtest/gtest.h"
#include "iostream"

using namespace std;



TEST(log, test_log_filehanlder)
{
    SLog* pstLog = new SLog();
    FileHandler* pstHandler = new FileHandler("log", E_LOG_LEVELToString(E_LOG_LEVEL::E_INFO));
    pstLog->RegisterHandler(E_LOG_LEVEL::E_INFO, pstHandler);
    pstLog->Log(E_LOG_LEVEL::E_INFO, "hello world");
    FileHandler* pstWarnHandler = new FileHandler("log", E_LOG_LEVELToString(E_LOG_LEVEL::E_WARN));
    pstLog->RegisterHandler(E_LOG_LEVEL::E_WARN, pstWarnHandler);
    pstLog->Log(E_LOG_LEVEL::E_WARN, "hello warn");
}

TEST(log, test_log_rotatingfilehandler)
{
    SLog* pstLog = new SLog();
    RotatingFileHandler* pstInfoHandler = new RotatingFileHandler("log", E_LOG_LEVELToString(E_LOG_LEVEL::E_INFO), 100, 2);
    pstLog->RegisterHandler(E_LOG_LEVEL::E_INFO, pstInfoHandler);
    pstLog->Log(E_LOG_LEVEL::E_INFO, "hello info 1");
    pstLog->Log(E_LOG_LEVEL::E_INFO, "hello info 2");
    pstLog->Log(E_LOG_LEVEL::E_INFO, "hello info 3");
}

TEST(log, test_file_size)
{
    char pszFilePath[MAX_LOG_FILE_DIR_PREFIX_SIZE * 2];
    sprintf(pszFilePath, "%s/%s_0.txt", "log", E_LOG_LEVELToString(E_LOG_LEVEL::E_INFO));
    struct stat sb{};
    if (stat(pszFilePath, &sb))
    {
        perror("stat get file size error");
    }
    cout << sb.st_size << endl;

}