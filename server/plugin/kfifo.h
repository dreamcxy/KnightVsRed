//
// Created by chenxiaoyu5 on 2022/6/22.
//

#ifndef SERVER_KFIFO_H
#define SERVER_KFIFO_H


// 模仿linux的kfifo设计的单生产者单消费者情况下的无锁环形循环队列

#include <cstdint>
#include <cstdlib>
#include <cstring>

/**
+--------------------------------------------------------------+
|            |<----------data---------->|                      |
+--------------------------------------------------------------+
^                          ^                      ^
|                          |                      |
out                        in                     size
**/

#define kfifo_min(x,y) ({ auto _x = (x); auto _y = (y); (void) (&_x == &_y); _x < _y ? _x : _y; })

namespace KFIFO
{
    static inline int fls(int x)
    {
        int position;
        int i;
        if(0 != x)
        {
            for (i = (x >> 1), position = 0; i != 0; ++position)
                i >>= 1;
        }
        else
        {
            position = -1;
        }
        return position+1;
    }

    struct STKFifo
    {

            char* m_pszBuffer;
            uint32_t   m_nSize;         // buffer初始化大小，会扩展成2的次幂
            uint32_t   m_nInOffset;     // 指向buffer的队头
            uint32_t   m_nOutOffset;    // 指向buffer的队尾
        //    spinlock_t*    m_Lock;        // 单生产者单消费者情况下，无需使用
    };

    inline uint32_t roundup_pow_of_tow(uint32_t nSize)
    {
        return 1UL << fls(nSize - 1);

    }

    // 调用这个函数，初始化一个size大小的kfifo
    STKFifo* KFifoAlloc(uint32_t nSize)
    {
        if (nSize > 0x80000000 || nSize <= 0)
        {
            return nullptr;
        }
        if (nSize & (nSize - 1))
        {
            nSize = roundup_pow_of_tow(nSize);
        }
        auto* pstFifo = new STKFifo();
        pstFifo->m_pszBuffer = (char * ) malloc(nSize);
        pstFifo->m_nSize = nSize;
        pstFifo->m_nInOffset = 0;
        pstFifo->m_nOutOffset = 0;
        return pstFifo;
    };

    uint32_t KFifoPut(STKFifo* pstKfifo, char* szData, uint32_t nLen)
    {
        uint32_t l = kfifo_min(nLen, pstKfifo->m_nSize - (pstKfifo->m_nInOffset & (pstKfifo->m_nOutOffset - 1)));
        memcpy(pstKfifo->m_pszBuffer + (pstKfifo->m_nInOffset & (pstKfifo->m_nSize - 1 )), szData, l);
        memcpy(pstKfifo->m_pszBuffer, szData + l, nLen - l);
        pstKfifo->m_nInOffset += nLen;
        return nLen;
    };

    uint32_t KFifoGet(STKFifo* pstKfifo, char* szBuffer, uint32_t nLen)
    {
        uint32_t l;
        nLen = kfifo_min(nLen, pstKfifo->m_nInOffset - pstKfifo->m_nOutOffset);
        l = kfifo_min(nLen, pstKfifo->m_nSize - (pstKfifo->m_nOutOffset & (pstKfifo->m_nSize - 1)));
        memcpy(szBuffer, pstKfifo->m_pszBuffer + (pstKfifo->m_nOutOffset & (pstKfifo->m_nSize - 1)), l);
        memcpy(szBuffer + l, pstKfifo->m_pszBuffer, nLen - l);
        return nLen;
    };

    // 清空一个kfifo的数据
    void KFifoClear(STKFifo* pstKfifo)
    {
        pstKfifo->m_nInOffset = pstKfifo->m_nOutOffset;
    }

    void KFifoFree(STKFifo* pstKfifo)
    {
        //todo
    }
}
#endif //SERVER_KFIFO_H

