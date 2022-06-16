#include "servertemplate.h"

int32_t CServerTemplater::Init()
{

    if (OnInit() != 0)
    {
        // 初始化失败
        assert(false);
        return -1;
    }

    return 0;
}

