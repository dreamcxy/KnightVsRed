//
// Created by cxy on 2022/8/2.
//


#include "logger.h"


STLogInstance SLog::m_stLogInstance = STLogInstance();

void SLog::Log(E_LOG_LEVEL eLogLevel, const char *pszContent)
{
    switch (eLogLevel) {
        case E_LOG_LEVEL::E_INFO:
        {
            m_stLogInstance.m_pstInfoHandler->Log(pszContent);
        }
            break;
        case E_LOG_LEVEL::E_WARN:
        {
            m_stLogInstance.m_pstWarnHandler->Log(pszContent);
        }
            break;
        case E_LOG_LEVEL::E_ERROR:
        {
            m_stLogInstance.m_pstErrorHandler->Log(pszContent);
        }
            break;
        default:
            break;
    }
}

void SLog::RegisterHandler(E_LOG_LEVEL eLogLevel, IHandlerBase *pstHandler)
{
    switch (eLogLevel) {
        case E_LOG_LEVEL::E_INFO:
        {
            m_stLogInstance.m_pstInfoHandler.reset(pstHandler);
        }
            break;
        case E_LOG_LEVEL::E_WARN:
        {
            m_stLogInstance.m_pstWarnHandler.reset(pstHandler);
        }
            break;
        case E_LOG_LEVEL::E_ERROR:
        {
            m_stLogInstance.m_pstErrorHandler.reset(pstHandler);
        }
            break;
        default:
            break;

    }
}