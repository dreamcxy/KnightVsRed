//
// Created by chenxiaoyu5 on 2022/8/2.
//


#include "handler.h"
#include "fileraii.h"
#include <string.h>
#include <sys/stat.h>

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
}

void RotatingFileHandler::Log(const char *pszContent)
{

    char pszFilePath[MAX_LOG_FILE_PATH_SIZE];
    sprintf(pszFilePath, "%s/%s_%d.txt", m_szDir, m_szFileName, m_nFileIndex);

    struct stat sb{};
    if (stat(pszFilePath, &sb))
    {
        // 不做处理，还没有这个文件
    }
    if (sb.st_size + strlen(pszContent) >= m_nFileSize)
    {
        // 当前文件大小超限
        if (m_nFileIndex + 1 >= m_nFileNum)
        {
            // 从0开始
            m_nFileIndex = 0;
        }
        else
        {
            m_nFileIndex += 1;
        }
    }

    char pszFileName[MAX_LOG_FILE_PATH_SIZE];
    sprintf(pszFileName, "%s_%d.txt", m_szFileName, m_nFileIndex);


    CFileRaii cFileRaii(m_szDir, pszFileName);
    cFileRaii.write(pszContent);

}