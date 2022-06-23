//
// Created by chenxiaoyu5 on 2022/6/23.
//

#include "networkmanager.h"
#include <sys/epoll.h>
#include <cassert>
#include <fcntl.h>

int32_t CNetworkManager::Initialize(STServerNetConfig& stConfig)
{

    int32_t nRet = 0;
    nRet += InitEpoll(stConfig);
    return nRet;
}

int32_t CNetworkManager::InitEpoll(STServerNetConfig &)
{
    // 随便填1个大于0的数就行，改版之后的epoll会根据连接自动分配内存
    int32_t nEpollFd = epoll_create1(9);
    if (nEpollFd == -1)
    {
        assert(false);
        return -1;
    }

    struct epoll_event stEv, eventList[1000];

}

int32_t CNetworkManager::SetSocketNonBlocking(int32_t nSocketFd)
{
    int32_t nOpts;
    nOpts = fcntl(nSocketFd, F_GETFL);
    if (nOpts < 0)
    {
        assert(false);
        return -1;
    }
    nOpts = nOpts | O_NONBLOCK;
    if (fcntl(nSocketFd, F_SETFL, nOpts) < 0)
    {
        assert(false);
        return -1;
    }
    return 0;
}
