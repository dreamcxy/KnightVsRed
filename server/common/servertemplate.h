/**
 * server 模板
 * 
**/


class CServerTemplate 
{
public:
    CServerTemplate() {}
    virtual ~CServerTemplate() {}

    int32_t Init();

public:
    
    // Init的最后一步调用，子类需要实现
    virtual int32_t OnInit() = 0;

public:
    bool m_bIsDeamon;   // 是否启动之后用变成守护进程
}