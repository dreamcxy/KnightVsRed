#include "servertemplate.h"
#include "gametime.h"
#include "servermanager.h"
#include <unistd.h>


int32_t CServerTemplater::Init()
{
    if (StartDemonProcess() != 0)
    {
        assert(false);
        return -1;
    }

    m_poGameTime = TSingleton<CGameTime>::GetInstance();
    if (unlikely(!m_poGameTime))
    {
        assert(false);
        return -1;
    }

    m_poServerMgr = TSingleton<CServerManager>::GetInstance();
    if (unlikely(!m_poServerMgr))
    {
        assert(false);
        return -1;
    }
    if (m_poServerMgr->Initialize() != 0)
    {
        assert(false);
        return -1;
    }

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

        OnTickEnd();
    }
    
}

int32_t CServerTemplate::HandleMsg()
{

}