//
// Created by cxy on 2022/6/22.
//
/**
 *  server端的时间管理
**/


#ifndef SERVER_GAMETIME_H
#define SERVER_GAMETIME_H

#include "singleton.h"
#include <sys/time.h>

class CGameTime : public TSingleton<CGameTime>
{
    DECLARE_CLASS_SINGLETON(CGameTime)

public:

    CGameTime();
    ~CGameTime() {};

public:
    int32_t GetCurSecond() { return m_stCurTimeVal.tv_sec; }
    uint32_t GetCurMSSecond() { return m_stCurTimeVal.tv_usec; }
    
    // 随着tick更新时间
    void Update();

private:
    struct timeval m_stCurTimeVal;
};

#endif //SERVER_GAMETIME_H
