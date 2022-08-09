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


class SLog
{
public:
    static void Log(E_LOG_LEVEL eLogLevel, const char* pszContent);
    static void RegisterHandler(E_LOG_LEVEL eLogLevel, IHandlerBase* pstHandler);
private:
    static std::map<E_LOG_LEVEL, std::unique_ptr<IHandlerBase>> m_mapLevelToHandler;

};



#define LOG_INFO()
#define LOG_DEBUG()
#define LOG_ERROR()

#endif //KNIGHTVSREDSERVER_LOGGER_H
