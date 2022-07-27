//
// Created by chenxiaoyu5 on 2022/7/1.
//

#ifndef SERVER_HANDLER_H
#define SERVER_HANDLER_H


#include "buffer.h"
#include <fstream>
#include "fileraii.h"

const std::string& GetPrefixByLevel(E_LOG_LEVEL eLogLevel)
{
    switch (eLogLevel)
    {
        case LOG_LEVEL_INFO:
            return "info";
        case LOG_LEVEL_WARN:
            return "warn";
        case LOG_LEVEL_ERROR:
            return "error";
        default:
            return "common";
    }
}

template <typename BufferT>
class FileHandler
// 直接写入文件，定时以及buffer长度大到一定长度
{
public:
    FileHandler() {}
    virtual ~FileHandler() {}

    FileHandler(E_LOG_LEVEL eLogLevel):m_eLogLevel(eLogLevel){}

public:
    void Log(char* pszContent);
    void Init(char* pszDir, char* pszPrefix);
    // 将内容写入
    void Flush();
    void Update();
private:
    E_LOG_LEVEL     m_eLogLevel;
    BufferT*        m_pstLogBuffer;

    char            m_szDir[MAX_LOG_FILE_DIR_PREFIX_SIZE];           // 文件夹根目录
    char            m_szPrefix[MAX_LOG_FILE_DIR_PREFIX_SIZE];        // 文件的前缀
};

template <typename BufferT>
void FileHandler<BufferT>::Log(char *pszContent)
{
    if (m_pstLogBuffer->OverFlow())
    {
        // 容量超过了预设上限
        char szFilePath[MAX_LOG_FILE_DIR_PREFIX_SIZE];
        snprintf("%s/%s", sizeof(szFilePath), m_szDir, m_szPrefix);

        CFileRaii cFileRaii(m_szDir, m_szPrefix);
        cFileRaii.write(pszContent);

        m_pstLogBuffer->Clear();
        return;
    }
    // todocxy 这边也直接写入文件
    m_pstLogBuffer->Put(pszContent);
}

template <typename BufferT>
void FileHandler<BufferT>::Init(char *pszDir, char *pszPrefix)
{
    // 默认输出到本目录下面, 以level作为前缀
    if (pszDir == nullptr)
    {
        strcpy(m_szDir, DEFAULT_LOG_DIR);
    }
    if (pszPrefix == nullptr)
    {
        strcpy(m_szPrefix, GetPrefixByLevel(m_eLogLevel));
    }
    // 萃取出来
    m_pstLogBuffer->Init();
}

template <typename BufferT>
void FileHandler<BufferT>::Update()
{
    // todocxy 定时写入
    if (!m_pstLogBuffer->empty())
    {
        Log("");
    }
}

template <typename BufferT>
void FileHandler<BufferT>::Flush()
{

}


template <typename BufferT>
class RotatingFileHandler : FileHandler<BufferT>
{
    // 根据文件大小进行轮转
public:

private:

};

template <typename BufferT>
class RotatingFileTimeHandler : FileHandler<BufferT>
{
    // 根据文件时间进行轮转
};


#endif //SERVER_HANDLER_H
