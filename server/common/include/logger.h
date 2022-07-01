//
// Created by chenxiaoyu5 on 2022/6/30.
// log 日志
//

#ifndef SERVER_LOGGER_H
#define SERVER_LOGGER_H


#include <kfifo.h>
#include <map>
#include "singleton.h"

enum E_LOG_LEVEL
{
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR
};

class BaseHandler
{

public:
    BaseHandler() {}
    virtual ~BaseHandler() {}

public:
    virtual void Log(char* pszContent);
    virtual void SetLevel(E_LOG_LEVEL eLogLevel) {m_eLogLevel = eLogLevel;}
private:
    // 是否满足轮转条件，默认不论转
    virtual bool IfSatisfyRotating() { return true;}
    virtual void Init(const std::string& strDir, const std::string& strPrefix);

private:
    E_LOG_LEVEL     m_eLogLevel;
    BaseLogBuffer*  m_pstLogBuffer;
};

class BaseLogBuffer
{
    // 默认是直接char*

};

class RotatingFileHandler : BaseHandler
{
    // 根据文件大小进行轮转
public:

private:

};

class RotatingFileTimeHandler : BaseHandler
{
    // 根据文件时间进行轮转
};

class SLog
{
public:
    int32_t Log(E_LOG_LEVEL eLogLevel, char* pszContent);
    void InitLog(char* pszDir, char* pszPrefix);

    // 根据时间将缓冲区的内容输出
    void Update();

    void SetLevelToHandler(E_LOG_LEVEL eLogLevel, BaseHandler* pstHandler) { m_mapLevelToHandler[eLogLevel] = pstHandler;}
private:
    BaseHandler* GetHandlerByLevel(E_LOG_LEVEL eLogLevel) { return m_mapLevelToHandler[eLogLevel];}
private:
    std::map<E_LOG_LEVEL, BaseHandler*> m_mapLevelToHandler;        // <日志等级，日志处理方式>
};




#endif //SERVER_LOGGER_H
