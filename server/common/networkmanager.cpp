//
// Created by chenxiaoyu5 on 2022/6/23.
//

#include "networkmanager.h"
#include <sys/epoll.h>
#include <cassert>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>


int32_t CNetworkManager::Initialize(const STAddressConfig& stConfig)
{

    int32_t nRet = 0;
    nRet += InitEpoll(stConfig);
    return nRet;
}

int32_t CNetworkManager::InitEpoll(const STAddressConfig& stConfig)
{
    // 先设置listensocket
    struct sockaddr_in stServerAddr = {0};
    int32_t nListenSockFd = socket(AF_INET, SOCK_STREAM, 0);
    if (nListenSockFd == -1)
    {
        assert(false);
        return -1;
    }

#ifdef DEBUG
    // 打开端口复用，避免测试出现addresss already in use的问题
    int32_t nOn = 1;
    if (setsockopt(nListeSockFd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1)
    {
        assert(false);
        return -1;
    }
#endif
    stServerAddr.sin_family = AF_INET;
    inet_aton(stConfig.m_strIP.c_str(), &(stServerAddr.sin_addr));
    stServerAddr.sin_port = htons(stConfig.m_nPort);
    if (bind(nListenSockFd, (const struct sockaddr *)&stServerAddr, sizeof(stServerAddr)) == -1)
    {
        assert(false);
        return -1;
    }
    if (SetSocketNonBlocking(nListenSockFd) != 0)
    {
        assert(false);
        return -1;
    }

    if (listen(nListenSockFd, MAX_LISTEN_SOCK_QUEUE) == -1)
    {
        assert(false);
        return -1;
    }

    if (nListenSockFd == 0)
    {
        assert(false);
        return -1;
    }

    // 创建epoll实例
    // 随便填1个大于0的数就行，改版之后的epoll会根据连接自动分配内存
    int32_t nEpollFd = epoll_create1(9);
    if (nEpollFd == 1)
    {
        assert(false);
        return -1;
    }

    struct epoll_event stEv, arrEvent[MAX_EVENT_LISTEN_NUM];
    stEv.events = EPOLLIN | EPOLLOUT | EPOLLET;
    stEv.data.fd = nListenSockFd;
    if (epoll_ctl(nEpollFd, EPOLL_CTL_ADD, nListenSockFd, &stEv) == -1)
    {
        assert(false);
        return -1;
    }

    while (true)
    {
        int32_t nWaitCount = epoll_wait(nEpollFd, arrEvent, MAX_EVENT_LISTEN_NUM, -1);
        if (nWaitCount == -1)
        {
            // 说明出问题了
            assert(false);
            return -1;
        }
        for (int i = 0; i < nWaitCount; i++)
        {
            auto events = arrEvent[i].events;
            char szHostBuf[NI_MAXHOST];
            if (events & EPOLLERR || events & EPOLLHUP || (!events & EPOLLIN))
            {
                close(arrEvent[i].data.fd);
                continue;
            }
            else if (nListenSockFd == arrEvent[i].data.fd)
            {
                // 表明是accept事件
                for (;;)
                {
                    // 由于是边缘触发，因此要循环读取
                    struct sockaddr stInAddr = {0};
                    socklen_t nLenStInAddr = sizeof(stInAddr);
                    int32_t nAcceptFd = accept(nListenSockFd, &stInAddr, &nLenStInAddr);
                    if (nAcceptFd == -1)
                    {
                        // todocxy 补充error日志
                        break;
                    }
                    if (SetSocketNonBlocking(nAcceptFd) != 0)
                    {
                        assert(false);
                        break;
                    }
                    stEv.events = EPOLLIN|EPOLLOUT|EPOLLET;
                    stEv.data.fd = nAcceptFd;
                    if (epoll_ctl(nEpollFd, EPOLL_CTL_ADD, nAcceptFd, &stEv) == -1)
                    {
                        assert(false);
                        exit(EXIT_FAILURE);
                    }
                }
            }
            else if (arrEvent[i].events & EPOLLIN)
            {
                // 读操作
                auto iter = m_mapSocketFdToConnection.find(arrEvent[i].data.fd);
                if (iter == m_mapSocketFdToConnection.end())
                {
                    assert(false);
                    continue;
                }
                iter->second.OnRecv();
            }
            else if (arrEvent[i].events & EPOLLOUT)
            {
                // 写操作
            }
            else
            {

            }
        }
    }

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
