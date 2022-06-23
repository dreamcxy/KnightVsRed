#pragma once
#include <cstdint>
#include "commondefine.h"

/**
 *  用来做网络管理的
 *  连接建立，网络包收发都通过这边进行
**/



class CNetworkManager
{
public:
    CNetworkManager() {}
    ~CNetworkManager() {}

    // 根据配置初始化网络底层
    int32_t Initialize(const STAddressConfig& );

private:
    // 初始化底层epoll
    int32_t InitEpoll(const STAddressConfig& );
    int32_t SetSocketNonBlocking(int32_t nSocketFd);
}
