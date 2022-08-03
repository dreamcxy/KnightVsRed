//
// Created by cxy on 2022/8/3.
//

#include "buffer.h"
#include <string.h>


void CharBuffer::Clear()
{
    memset(m_szBuffer, 0, MAX_LOG_BUFFER_SIZE);
}

bool CharBuffer::OverFlow(int32_t nLength)
{
    return nLength + strlen(m_szBuffer) >= MAX_LOG_BUFFER_SIZE;
}

void CharBuffer::Put(const char *pszContent)
{
    strncat(m_szBuffer, pszContent, strlen(pszContent));
}

bool CharBuffer::Empty()
{
    return strlen(m_szBuffer) == 0;
}

char* CharBuffer::GetContent()
{
    return m_szBuffer;
}

int32_t CharBuffer::GetBufferSize()
{
    return strlen(m_szBuffer);
}