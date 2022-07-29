//
// Created by chenxiaoyu5 on 2022/7/1.
//

#ifndef SERVER_BUFFER_H
#define SERVER_BUFFER_H

#include "commondefine.h"
class CharLogBuffer
{
    // 默认是直接char*
public:
    CharLogBuffer() {}
    virtual ~CharLogBuffer() {}

    CharLogBuffer(int32_t nSize)
    {

        m_nSize = nSize;
        InitBuffer();
    }

    void InitBuffer();

    // 容量是否超上限了
    bool OverFlow(int32_t nLen);
    // 清空buffer
    void Clear();
    // 添加内容
    void Put(char* pszContent);

    bool empty() {return m_nUsed == 0; };
private:
    char* m_pszBuffer;
    int32_t m_nSize = MAX_LOG_BUFFER_SIZE;    // 上限
    int32_t m_nUsed;                          // 已经使用了的长度
};


class FifoLogBuffer
{
    // 环形队列
public:
};


#endif //SERVER_BUFFER_H
