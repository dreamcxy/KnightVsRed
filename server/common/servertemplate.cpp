#include "servertemplate.h"
#include "gametime.h"
#include "servermanager.h"
#include "networkmanager.h"
#include <unistd.h>
#include <stdio.h>
#include <cassert>


int32_t CServerTemplate::Init()
{
    if (StartDaemonProcess() != 0)
    {
        assert(false);
        return -1;
    }

    m_poGameTime = TSingleton<CGameTime>::GetInstance();
    if (!m_poGameTime)
    {
        assert(false);
        return -1;
    }

    m_poServerMgr = TSingleton<CServerManager>::GetInstance();
    if (!m_poServerMgr)
    {
        assert(false);
        return -1;
    }
    if (m_poServerMgr->Initialize() != 0)
    {
        assert(false);
        return -1;
    }

    InitNetwork();

    if (OnInit() != 0)
    {
        // 初始化失败
        assert(false);
        return -1;
    }


    return 0;
}

int32_t CServerTemplate::StartDaemonProcess(char *pszWorkDir)
{
    if (!m_bIsDaemon)
    {
        return 0;
    }

    // 两次fork，每次都让父进程退出，是为了子进程
    if (fork() != 0)
    {
        exit(0);
    }
    if (setsid() < 0)
    {
        return -1;
    }
    if (fork() != 0)
    {
        exit(0);
    }

    // 允许创建的进程对创建的文件或者目录最大操作权限，避免后续创建文件或者目录的时候的权限的不确定性
    umask(0);
    if (pszWorkDir)
    {
        if (chdir(pszWorkDir) != 0)
        {
            return -1;
        }
    }
    else
    {
        if (chidr("/") !=0)
        {
            return -1;
        }
    }

    fclose(stdin);
    fclose(stdout);
    fclose(stderr);
    return 0;
}

void CServerTemplate::MainLoop()
{
    int32_t nStartTime = m_poGameTime->GetCurSecond();
    if (OnEnterMainLoop() != 0 )
    {
        assert(false);
        return;
    }
    while (true)
    {
        m_poGameTime->Update();
        OnTickBegin();
        int32_t nMsgCount = HandleMsg();
        if (nMsgCount == 0)
        {
            // 当前帧没有处理消息，就休息一会儿，避免CPU占满100%
            m_poNetworkMgr
        }
        OnTickEnd();
    }
    
}

int32_t CServerTemplate::HandleMsg()
{

}

int32_t CServerTemplate::InitNetwork()
{
    m_poNetworkMgr = new CNetworkManager();
    if (!m_poNetworkMgr)
    {
        assert(false);
        return -1;
    }
    if (m_poNetworkMgr->Initialize() != 0)
    {
        assert(false);
        return -1;
    }
    return 0;
}
