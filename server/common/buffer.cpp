//
// Created by chenxiaoyu5 on 2022/7/1.
//

#include "include/buffer.h"
#include <string.h>



bool CharLogBuffer::OverFlow(int32_t nLen)
{
    return m_nUsed + nLen >= m_nSize;
}

void CharLogBuffer::Clear()
{
    memset(m_pszBuffer, 0, m_nSize);
}

void CharLogBuffer::Put(const char *pszContent)
{

}
