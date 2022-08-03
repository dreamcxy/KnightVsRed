//
// Created by cxy on 2022/8/2.
//


#include "logger.h"

void SLog::Log(E_LOG_LEVEL eLogLevel, const char *pszContent)
{
    auto iter = m_mapLevelToHandler.find(eLogLevel);
    if (iter == m_mapLevelToHandler.end() || iter->second == nullptr)
    {
        return;
    }
    iter->second.get()->Log(pszContent);
}

void SLog::RegisterHandler(E_LOG_LEVEL eLogLevel, IHandlerBase *pstHandler)
{
    m_mapLevelToHandler[eLogLevel].reset(pstHandler);
}