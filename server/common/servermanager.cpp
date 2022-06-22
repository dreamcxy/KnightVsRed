#include "servermanager.h"
#include <fcntl.h>
#include <sys/epoll.h>

int32_t CServerManager::Initialize()
{
    m_nEpfd = epoll_create1(0);
    if (m_nEpfd == 1)
    {
        assert(false);
        return -1;
    }


    return 0;
}


int32_t CServerManager::MakeSocketNonBlocking(int fd)
{
    int flags, s;
    flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1)
    {
        assert(false);
        return -1;
    }
}

int32_t CServerManager::Update()
{
    // 每帧调用，监听socker有哪些就绪事件
    int32_t number = epoll_wait(m_nEpfd, );
    struct epoll_event events[];
    // 遍历就绪的事件
    for (int i = 0; i < number; i++)
    {
        if (events & EPOLLERR || events & EPOLLHUP || (!events & EPOLLIN))
        {
            close(event)
        }    
    }
}