/**
 * server 模板
 * 
**/

class CGameTime;

class CServerTemplate 
{
public:
    CServerTemplate() {}
    virtual ~CServerTemplate() {}

    int32_t Init();
    void MainLoop();

    void SetDaemon(bool bIsDaemon) { m_bIsDaemon = bIsDaemon; }

public:
    
    // Init的最后一步调用，子类需要实现
    virtual int32_t OnInit() = 0;

    // 进入server的循环前所做的事情
    virtual int32_t OnEnterMainLoop() { return 0;}

    // 每一帧开始前调用
    virtual int32_t OnTickBegin() { return 0; }
    // 每一帧结束时调用
    virtual int32_t OnTickEnd() { return 0; }

private:
    int32_t StartDaemonProcess(char *pszWorkDir);

public:
    bool m_bIsDaemon;   // 是否启动之后用变成守护进程
    CGameTime *m_poGameTime = nullptr;
}