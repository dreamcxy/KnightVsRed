#include <cstdint>

/**
 * server 模板
 * 
**/
#pragma once

class CGameTime;
class CServerManager;
class CNetworkManager;

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

    // 处理收到的客户端发包
    virtual int32_t HandleMsg();

    // 开始运行
    virtual void Run(int argc,char *argv[]);
private:
    int32_t StartDaemonProcess(char *pszWorkDir = nullptr);

    int32_t InitNetwork();

public:
    bool m_bIsDaemon;   // 是否启动之后用变成守护进程
    CGameTime*          m_poGameTime = nullptr;
    CServerManager*     m_poServerMgr = nullptr;
    CNetworkManager*    m_poNetworkMgr = nullptr;

};
