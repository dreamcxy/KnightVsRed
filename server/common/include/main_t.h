/**
 * 所有server的启动 
**/ 

#include<singleton.h>

template<typename ConcreteServer>
class TMainTemplate
{
    void Run(int argc, char *argv[]);
}

template<typename ConcreteServer>
void TMainTemplate<ConcreteServer>::Run(int argc, char *argv[])
{
    ConcreteServer *poSvr = TSingleton<ConcreteServer>::GetInstance();
    if (unlikely(!poSvr))
    {
        assert(false);
        return;
    }

    poSvr->SetDaemon(false);

    while (-1 != (iOpt = getopt(argc, argv, "dhvc:s:t:")))
    {
        switch (iOpt)
        {
            case 'd':
                poSvr->SetDaemon(true);
                break;
            default:
                break;
        }
    }
}

