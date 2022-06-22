

#include "singleton.h"

class CServerManager : public TSingleton<CServerManager>
{
    DECLARE_CLASS_SINGLETON(CServerManager)
public:
    CServerManager(/* args */);
    ~CServerManager();

    // 初始化epoll之类的操作
    int32_t Initialize();

    int32_t MakeSocketNonBlocking(int fd);

    int32_t Update();

private:
    int32_t m_nEpfd;
};
