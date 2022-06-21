

class CServerManager
{
public:
    CServerManager(/* args */);
    ~CServerManager();

    // 初始化epoll之类的操作
    void Initialize();

    int32_t MakeSocketNonBlocking(int fd);

};
