//
// Created by cxy on 2022/8/2.
//

#ifndef KNIGHTVSREDSERVER_LOGGER_H
#define KNIGHTVSREDSERVER_LOGGER_H

#include "commondefine.h"
#include "handler.h"
#include <memory>
#include <map>



class ILoggerBase
{
public:
    ILoggerBase() { }
    virtual ~ILoggerBase() {}

    virtual void Log(E_LOG_LEVEL eLogLevel, const char* pszContent) = 0;
    virtual void RegisterHandler(E_LOG_LEVEL eLogLevel, IHandlerBase* pstHandler) = 0;

public:
    E_LOG_LEVEL m_eLogLevel;
};

struct STLogInstance
{
    std::unique_ptr<IHandlerBase> m_pstInfoHandler;
    std::unique_ptr<IHandlerBase> m_pstWarnHandler;
    std::unique_ptr<IHandlerBase> m_pstErrorHandler;
};

class SLog
{
public:
    static void Log(E_LOG_LEVEL eLogLevel, const char* pszContent);
    static void RegisterHandler(E_LOG_LEVEL eLogLevel, IHandlerBase* pstHandler);
private:
//    static std::map<E_LOG_LEVEL, std::unique_ptr<IHandlerBase>> m_mapLevelToHandler;
    static STLogInstance m_stLogInstance;
};



#define LOGINFO(format, ...) \
do{                           \
    int32_t nSize = snprintf(NULL, 0, format "...[%s:%s():%d]", ##__VA_ARGS__, __FILE__, __FUNCTION__, __LINE__); \
    nSize++;                   \
    char* szBuf = (char*) malloc (nSize);                       \
    snprintf(szBuf, nSize, format "...[%s:%s():%d]", ##__VA_ARGS__, __FILE__, __FUNCTION__, __LINE__);\
    SLog::Log(E_LOG_LEVEL::E_INFO, szBuf);                    \
    free(szBuf);                             \
}while(0)

#define LOGWARN(format, ...) \
do{                           \
    int32_t nSize = snprintf(NULL, 0, format "...[%s:%s():%d]", ##__VA_ARGS__, __FILE__, __FUNCTION__, __LINE__); \
    nSize++;                   \
    char* szBuf = (char*) malloc (nSize);                       \
    snprintf(szBuf, nSize, format "...[%s:%s():%d]", ##__VA_ARGS__, __FILE__, __FUNCTION__, __LINE__);\
    SLog::Log(E_LOG_LEVEL::E_WARN, szBuf);                    \
    free(szBuf);                             \
}while(0)

#define LOGERROR(format, ...) \
do{                           \
    int32_t nSize = snprintf(NULL, 0, format "...[%s:%s():%d]", ##__VA_ARGS__, __FILE__, __FUNCTION__, __LINE__); \
    nSize++;                   \
    char* szBuf = (char*) malloc (nSize);                       \
    snprintf(szBuf, nSize, format "...[%s:%s():%d]", ##__VA_ARGS__, __FILE__, __FUNCTION__, __LINE__);\
    SLog::Log(E_LOG_LEVEL::E_ERROR, szBuf);                    \
    free(szBuf);                             \
}while(0)

#endif //KNIGHTVSREDSERVER_LOGGER_H
