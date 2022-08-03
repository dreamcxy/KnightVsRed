//
// Created by cxy on 2022/8/2.
//

#ifndef KNIGHTVSREDSERVER_BUFFER_H
#define KNIGHTVSREDSERVER_BUFFER_H

#include <cstdint>
#include "commondefine.h"

class IBufferBase
{
public:
    IBufferBase() {}
    virtual ~IBufferBase() {}

    virtual void Clear() = 0;
    virtual bool OverFlow(int32_t nLength) = 0;
    virtual void Put(const char* pszContent) = 0;
    virtual bool Empty() = 0;
    virtual int32_t GetBufferSize() = 0;
    virtual char* GetContent() = 0;
};

class CharBuffer : public IBufferBase
{
public:
    CharBuffer() {}
    virtual ~CharBuffer() {}

    virtual void Clear() override;
    virtual bool OverFlow(int32_t nLength) override;
    virtual void Put(const char* pszContent) override;
    virtual bool Empty() override;
    virtual char* GetContent() override;
    virtual int32_t GetBufferSize() override;

private:
    char m_szBuffer[MAX_LOG_BUFFER_SIZE];
};



#endif //KNIGHTVSREDSERVER_BUFFER_H


