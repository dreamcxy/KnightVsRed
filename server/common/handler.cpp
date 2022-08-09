//
// Created by cxy on 2022/8/2.
//


#include "handler.h"
#include "fileraii.h"
#include "fileutils.h"
#include <string.h>
#include <sys/stat.h>

#include <memory>
#include <functional>
#include "algorithm"

FileHandler::FileHandler(const char *pszDir, const char *pszFileName)
{
    strncpy(m_szDir, pszDir, strlen(pszDir) + 1);
    strncpy(m_szFileName, pszFileName, strlen(pszFileName) + 1);
}


void FileHandler::Log(const char *pszContent)
{
    if (pszContent == nullptr)
    {
        return;
    }
    if (strlen(m_szDir) == 0 || strlen(m_szFileName) == 0)
    {
        CFileRaii cFileRaii(DEFAULT_LOG_DIR, DEFAULT_LOG_FILE_NAME);
        cFileRaii.write(pszContent);
    }
    else
    {
        CFileRaii cFileRaii(m_szDir, m_szFileName);
        cFileRaii.write(pszContent);
    }
}

void FileHandler::LogDirect(const char *pszContent)
{
    Log(pszContent);
}

void FileHandler::SetBuffer(IBufferBase *pstBuffer)
{
    if (!m_pstBuffer->Empty())
    {
        // 将buffer里面的写入文件
        Log(m_pstBuffer->GetContent());
    }
    m_pstBuffer.reset(pstBuffer);
}

/////////////////////////////////////////RotatingFileHandler////////////////////////////////////////////////////////////
RotatingFileHandler::RotatingFileHandler(const char *pszDir, const char *pszFileName, int32_t nFileSize,
                                         int32_t nFileNum)
{
    strncpy(m_szDir, pszDir, strlen(pszDir) + 1);
    strncpy(m_szFileName, pszFileName, strlen(pszFileName) + 1);
    m_nFileNum = nFileNum;
    m_nFileSize = nFileSize;
    m_pstBuffer = std::make_unique<CharBuffer>();
    m_nFileIndex = 0;
}

RotatingFileHandler::~RotatingFileHandler()
{
    LogDirect(m_pstBuffer->GetContent());
}

void RotatingFileHandler::Log(const char *pszContent)
{
    if (m_pstBuffer->OverFlow(strlen(pszContent)))
    {
        // 如果加入就会超过buffer的大小
        LogDirect(m_pstBuffer->GetContent());
        LogDirect(pszContent);
        m_pstBuffer->Clear();
        return;
    }
    m_pstBuffer->Put(pszContent);
}

void RotatingFileHandler::LogDirect(const char *pszContent)
{
    if (strlen(pszContent) == 0)
    {
        return;
    }
    char pszFilePath[MAX_LOG_FILE_PATH_SIZE];
    sprintf(pszFilePath, "%s/%s_%d.txt", m_szDir, m_szFileName, 0);
    if (FileUtils::GetFileSize(pszFilePath) + strlen(pszContent) >= m_nFileSize)
    {
        // 当前文件大小超限
        // 将0备份到1
        if (m_nFileIndex + 1 >= m_nFileNum)
        {
            // 从0开始
            m_nFileIndex = 0;
        }
        else
        {
            m_nFileIndex += 1;
        }

        // 清空文件
        sprintf(pszFilePath, "%s/%s_%d.txt", m_szDir, m_szFileName, m_nFileIndex);
        std::ofstream writer(pszFilePath, std::ios_base::out);
    }
    char pszFileName[MAX_LOG_FILE_PATH_SIZE];
    sprintf(pszFileName, "%s_%d.txt", m_szFileName, m_nFileIndex);

    CFileRaii cFileRaii(m_szDir, pszFileName);
    cFileRaii.write(pszContent);

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RotatingFileTimeHandler::~RotatingFileTimeHandler() noexcept
{
    LogDirect(m_pstBuffer->GetContent());
}

RotatingFileTimeHandler::RotatingFileTimeHandler(const char *pszDir, const char *pszFileName, int32_t nFileSize,
                                                 int32_t nFileNum)
{
    strncpy(m_szDir, pszDir, strlen(pszDir) + 1);
    strncpy(m_szFileName, pszFileName, strlen(pszFileName) + 1);
    m_nFileNum = nFileNum;
    m_nFileSize = nFileSize;
    m_pstBuffer = std::make_unique<CharBuffer>();
    // 读取目录下面的文件，看到哪个目录了
    m_nCurFileIndex = GetCurLogFileIndex();
}


void RotatingFileTimeHandler::Log(const char *pszContent)
{
    if (m_pstBuffer->OverFlow((int32_t)strlen(pszContent)))
    {
        LogDirect(m_pstBuffer->GetContent());
        LogDirect(pszContent);
        m_pstBuffer->Clear();
        return;
    }
    m_pstBuffer->Put(pszContent);
}

void RotatingFileTimeHandler::LogDirect(const char *pszContent)
{
    // 文件根据时间轮转，写入的文件都是0开头的， 根据文件大小，将0备份到1
    char pszFilePath[MAX_LOG_FILE_PATH_SIZE];
    sprintf(pszFilePath, "%s/%s_%d.txt", m_szDir, m_szFileName, 0);
    if (FileUtils::GetFileSize(pszFilePath) + strlen(pszContent) >= m_nFileSize)
    {
        // 迁移文件
        char pszNewFileName[MAX_LOG_FILE_PATH_SIZE];
        sprintf(pszNewFileName, "%s_%d.txt", m_szFileName, GetNextBackupIndex());
        char pszOldFileName[MAX_LOG_FILE_PATH_SIZE];
        sprintf(pszOldFileName, "%s_%d.txt", m_szFileName, 0);
        FileUtils::RenameFileSameDir(m_szDir, pszOldFileName, pszNewFileName);
    }
    // 写入文件
    char pszFileName[MAX_LOG_FILE_PATH_SIZE];
    sprintf(pszFileName, "%s_%d.txt", m_szFileName, 0);
    CFileRaii cFileRaii(m_szDir, pszFileName);
    cFileRaii.write(pszContent);

}

int32_t RotatingFileTimeHandler::GetCurLogFileIndex()
{
    std::vector<std::string>&& vecFiles = FileUtils::GetFilesInDir(m_szDir, m_szFileName);
    if (vecFiles.empty() || vecFiles.size() == 1)
    {
        return 0;
    }
    std::function<bool(std::string , std::string )> oFileSortByMtime = [](std::string  strFilePath1,  std::string  strFilePath2) -> bool
    {
        int32_t nPointIndex1 = strFilePath1.find('.', 0);
        int32_t nPointIndex2 = strFilePath2.find('.', 0);
        int32_t nIndex1 = atoi(strFilePath1.substr(nPointIndex1-1, 1).c_str());
        int32_t nIndex2 = atoi(strFilePath2.substr(nPointIndex2-1, 1).c_str());
        return nIndex2 < nIndex1;
    };
    std::sort(vecFiles.begin(), vecFiles.end(), oFileSortByMtime);
    const std::string& strFile = vecFiles[0];
    int32_t nPointIndex = strFile.find('.', 0);
    return atoi(strFile.substr(nPointIndex-1, 1).c_str());
}

int32_t RotatingFileTimeHandler::GetNextBackupIndex()
{
    m_nCurFileIndex = (m_nCurFileIndex % m_nFileNum) + 1;
    return m_nCurFileIndex;
}