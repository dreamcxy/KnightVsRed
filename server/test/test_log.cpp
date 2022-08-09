//
// Created by cxy on 2022/7/29.
//


#include "logger.h"
#include "gtest/gtest.h"
#include "iostream"
#include "fileutils.h"

using namespace std;


TEST(log, test_log_filehanlder)
{
    return;
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
    return;
    SLog* pstLog = new SLog();
    RotatingFileHandler* pstInfoHandler = new RotatingFileHandler("log", E_LOG_LEVELToString(E_LOG_LEVEL::E_INFO), 100, 2);
    pstLog->RegisterHandler(E_LOG_LEVEL::E_INFO, pstInfoHandler);
    pstLog->Log(E_LOG_LEVEL::E_INFO, "hello info 1");
    pstLog->Log(E_LOG_LEVEL::E_INFO, "hello info 2");
    pstLog->Log(E_LOG_LEVEL::E_INFO, "hello info 3");
}

TEST(log, test_log_rotatingfiletimehandler)
{
    RotatingFileTimeHandler* pstInfoHandler = new RotatingFileTimeHandler("log", E_LOG_LEVELToString(E_LOG_LEVEL::E_INFO),
                                                                          100, 5);
    SLog::RegisterHandler(E_LOG_LEVEL::E_INFO, pstInfoHandler);
    RotatingFileTimeHandler* pstWarnHandler = new RotatingFileTimeHandler("log", E_LOG_LEVELToString(E_LOG_LEVEL::E_WARN),
                                                                          100, 5);
    SLog::RegisterHandler(E_LOG_LEVEL::E_WARN, pstWarnHandler);
    RotatingFileTimeHandler* pstErrorHandler = new RotatingFileTimeHandler("log", E_LOG_LEVELToString(E_LOG_LEVEL::E_ERROR),
                                                                          100, 5);
    SLog::RegisterHandler(E_LOG_LEVEL::E_ERROR, pstErrorHandler);
    int32_t nIndex = 0;
    while ( nIndex < 100)
    {
        nIndex++;
//        string strMsg = "hello info" + to_string(nIndex);
//        SLog::Log(E_LOG_LEVEL::E_INFO, strMsg.c_str());
        LOGINFO("hello info %d", nIndex);
        LOGWARN("hello warn %d", nIndex);
        LOGERROR("hello error %d", nIndex);
    }
}

TEST(log, test_file_size)
{
    return;
    char pszFilePath[MAX_LOG_FILE_DIR_PREFIX_SIZE * 2];
    sprintf(pszFilePath, "%s/%s_0.txt", "log", E_LOG_LEVELToString(E_LOG_LEVEL::E_INFO));
    struct stat sb{};
    if (stat(pszFilePath, &sb))
    {
        perror("stat get file size error");
    }
    cout << sb.st_size << endl;
}

TEST(log, test_char_array)
{
    return;
    CharBuffer charBuffer = CharBuffer();
    cout << charBuffer.Empty() << endl;
    charBuffer.Put("hello world");
    cout << charBuffer.GetBufferSize() << endl;
    cout << charBuffer.GetContent() << endl;
    charBuffer.Clear();
    cout << charBuffer.GetBufferSize() << endl;
}

TEST(log, test_file_utils_get)
{
    // 测试获取文件
    return;
    const char* pszDirName = "log";
    std::vector<string > && vecFiles = FileUtils::GetFilesInDir(pszDirName, nullptr);
    for (auto file : vecFiles)
    {
        cout << file << endl;
    }
    vecFiles = FileUtils::GetFilesInDir(pszDirName, "E_INFO");
    for (auto file : vecFiles)
    {
        cout << file << endl;
    }
    vecFiles = FileUtils::GetFilesInDir(pszDirName, "E_ERROR");
    if (vecFiles.empty())
    {
        cout << "empty" << endl;
    }
    for (auto file : vecFiles)
    {
        cout << file << endl;
    }
}

TEST(log, test_file_time_sort)
{
    return;
    const char* pszDirName = "log";
    string&& file = FileUtils::GetLatestFileInDir(pszDirName, nullptr);
    cout << file << endl;
}