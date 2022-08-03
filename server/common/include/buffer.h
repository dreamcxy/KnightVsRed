//
// Created by chenxiaoyu5 on 2022/8/2.
//

#ifndef KNIGHTVSREDSERVER_BUFFER_H
#define KNIGHTVSREDSERVER_BUFFER_H

#include <cstdint>

class IBufferBase
{
public:
    IBufferBase() {}
    virtual ~IBufferBase() {}

    virtual void Clear() = 0;
    virtual bool OverFlow(int32_t nLength) = 0;
    virtual void Put(const char* pszContent) = 0;
    virtual bool Empty() = 0;
    virtual char* GetContent() = 0;
};

class CharBuffer : public IBufferBase
{
public:
    CharBuffer() {}
    virtual ~CharBuffer() {}

};



#endif //KNIGHTVSREDSERVER_BUFFER_H


