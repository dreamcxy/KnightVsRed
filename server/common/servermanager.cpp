#include "servermanager.h"
#include <fcntl.h>

void CServerManager::Initialize()
{

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