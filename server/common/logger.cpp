//
// Created by chenxiaoyu5 on 2022/6/30.
//


#include "include/logger.h"
#include "include/commondefine.h"

void BaseHandler::Log(char *pszContent)
{

}

void BaseHandler::Init(char *pszDir, char *pszPrefix)
{
    // 默认输出到本目录下面, 以level作为前缀
    if (pszDir == nullptr)
    {

    }
    if (pszPrefix == nullptr)
    {

    }
}



int32_t SLog::Log(E_LOG_LEVEL eLogLevel, char *pszContent)
{
    auto pstHandler = GetHandlerByLevel(eLogLevel);
    if (!pstHandler)
    {
        return -1;
    }
    pstHandler->Log(pszContent);
}

void SLog::Update()
{

}
