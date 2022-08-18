//
// Created by chenxiaoyu5 on 2022/8/10.
//

#ifndef KNIGHTVSREDSERVER_HOMESERVER_H
#define KNIGHTVSREDSERVER_HOMESERVER_H
#include "servertemplate.h"
#include "singleton.h"

class CHomeServer : public CServerTemplate, public TSingleton<CHomeServer>
{
    DECLARE_CLASS_SINGLETON(CHomeServer)
public:


};


#endif //KNIGHTVSREDSERVER_HOMESERVER_H
