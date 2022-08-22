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

    CHomeServer(){}
    ~CHomeServer() {}

    // Init的最后一步调用，子类需要实现
    virtual int32_t OnInit() {return 0;};

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
};


#endif //KNIGHTVSREDSERVER_HOMESERVER_H
