//
// Created by chenxiaoyu5 on 2022/6/30.
// log 日志
//

#ifndef SERVER_LOGGER_H
#define SERVER_LOGGER_H


#include <kfifo.h>
#include <map>
#include "singleton.h"
#include "handler.h"

template <typename Handler>
class SLog : public TSingleton<SLog<Handler>>
{
    DECLARE_CLASS_SINGLETON(SLog<Handler>)
public:
    ~SLog()
    {
        for (auto& handler : m_mapLevelToHandler)
        {
            handler.second->Flush();
        }
    }

    SLog()
    {
//        m_mapLevelToHandler[E_LOG_LEVEL::E_INFO] = new Handler();
//        m_mapLevelToHandler[E_LOG_LEVEL::E_WARN] = new Handler();
//        m_mapLevelToHandler[E_LOG_LEVEL::E_ERROR] = new Handler();
        InitLog();
    }

    int32_t Log(E_LOG_LEVEL eLogLevel, const char* pszContent);
    int32_t InitLog(char* pszDir = nullptr, char* pszPrefix = nullptr);

    // 根据时间将缓冲区的内容输出
    void Update();
    void SetLevelToHandler(E_LOG_LEVEL eLogLevel, Handler* pstHandler) { m_mapLevelToHandler[eLogLevel] = pstHandler;}
private:

    Handler* GetHandlerByLevel(E_LOG_LEVEL eLogLevel) { return m_mapLevelToHandler[eLogLevel];}
private:

    std::map<E_LOG_LEVEL , Handler* > m_mapLevelToHandler;        // <日志等级，日志处理方式>
};

template <typename Handler>
int32_t SLog<Handler>::InitLog(char *pszDir, char *pszPrefix)
{
    for (auto e = E_LOG_LEVEL::E_INFO; e <= E_LOG_LEVEL::E_ERROR; e = (E_LOG_LEVEL)(int(e) + 1))
    {
        // 默认初始化不同level的日志的handler
        m_mapLevelToHandler[e] = new FileHandler<CharLogBuffer>(e);
        m_mapLevelToHandler[e]->Init(pszDir, pszPrefix);
    }

    return 0;
}

template <typename Handler>
int32_t SLog<Handler>::Log(E_LOG_LEVEL eLogLevel, const char *pszContent)
{
    auto pstHandler = GetHandlerByLevel(eLogLevel);
    if (!pstHandler)
    {
        return -1;
    }
    pstHandler->Log(pszContent);
}

template <typename Handler>
void SLog<Handler>::Update()
{
    for (auto handler : m_mapLevelToHandler)
    {
        handler.second->Update();
    }
}

template class SLog<FileHandler<CharLogBuffer>>;

#endif //SERVER_LOGGER_H
