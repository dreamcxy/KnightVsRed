//
// Created by cxy on 2022/8/2.
//

#ifndef KNIGHTVSREDSERVER_HANDLER_H
#define KNIGHTVSREDSERVER_HANDLER_H

#include "buffer.h"
#include "commondefine.h"
#include <memory>

class IHandlerBase
{
public:
    IHandlerBase() {}
    virtual ~IHandlerBase() {}

    virtual void Log(const char* pszContent) = 0;
    // 直接落盘存储
    virtual void LogDirect(const char* pszContent) = 0;
//    virtual void SetBuffer(IBufferBase* pstBuffer) = 0;
};

// 这个是直接写入文件
class FileHandler : public IHandlerBase
{
public:
    FileHandler() = default;
    virtual ~FileHandler() {}

    FileHandler(const char *pszDir, const char* pszFileName);

    virtual void Log(const char* pszContent) override;
    virtual void LogDirect(const char* pszContent) override;
    virtual void SetBuffer(IBufferBase* pstBuffer);
private:
    char m_szDir[MAX_LOG_FILE_DIR_PREFIX_SIZE];
    char m_szFileName[MAX_LOG_FILE_DIR_PREFIX_SIZE];
    std::unique_ptr<IBufferBase> m_pstBuffer;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 这个是根据文件大小进行轮转
class RotatingFileHandler : public IHandlerBase
{
public:
    RotatingFileHandler() = default;
    virtual ~RotatingFileHandler();

    RotatingFileHandler(const char* pszDir, const char* pszFileName, int32_t nFileSize, int32_t nFileNum);

    virtual void Log(const char* pszContent) override;
    virtual void LogDirect(const char* pszContent) override;


private:
    int32_t m_nFileSize;
    int32_t m_nFileNum;
    char    m_szDir[MAX_LOG_FILE_DIR_PREFIX_SIZE];
    char    m_szFileName[MAX_LOG_FILE_DIR_PREFIX_SIZE];
    int32_t m_nFileIndex; // 目前用的哪个文件
    std::unique_ptr<IBufferBase> m_pstBuffer;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class RotatingFileTimeHandler : public IHandlerBase
{
public:
    RotatingFileTimeHandler() = default;
    virtual ~RotatingFileTimeHandler();

    RotatingFileTimeHandler(const char* pszDir, const char* pszFileName, int32_t nFileSize, int32_t nFileNum);


    virtual void Log(const char* pszContent) override;
    virtual void LogDirect(const char* pszContent) override;

    int32_t GetCurIndex() { return m_nCurFileIndex; }

private:
    // 获取目录下面除0之外最新的日志文件的index
    int32_t GetCurLogFileIndex();
    // 获取下一个0应该备份成的index
    int32_t GetNextBackupIndex();

private:
    std::unique_ptr<IBufferBase> m_pstBuffer;
    int32_t m_nFileSize;
    int32_t m_nFileNum;
    char    m_szDir[MAX_LOG_FILE_DIR_PREFIX_SIZE];
    char    m_szFileName[MAX_LOG_FILE_DIR_PREFIX_SIZE];

    int32_t m_nCurFileIndex;
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif //KNIGHTVSREDSERVER_HANDLER_H
