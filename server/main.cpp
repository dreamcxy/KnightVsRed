// 其实是个测试程序
#include <iostream>
#include <cassert>
#include <thread>
#include "kfifo.h"
#include "common/include/logger.h"

#define N ((1 << 20))
void Producer(KFIFO::STKFifo* pstFifo)
{
    int i = 0;
    while (i < N)
    {
        char buffer[20];
        snprintf(buffer, sizeof(buffer), "hello world");
        KFIFO::KFifoPut(pstFifo, buffer, sizeof(buffer));
        i++;
    }
}

void Consumer(KFIFO::STKFifo* pstFifo)
{
    int i = 0;
    while (i < N)
    {
        char buffer[20];
        KFIFO::KFifoGet(pstFifo, buffer, 11);
        std::cout << buffer << std::endl;
        i ++;
    }
};

int main()
{
//    uint32_t size = 10;
//    auto pstFifo = KFIFO::KFifoAlloc(size);
//    if (pstFifo == nullptr)
//    {
//        assert(false);
//        return -1;
//    }
//
//    std::thread producer(Producer, pstFifo);
//    std::thread consumer(Consumer, pstFifo);
//
//    producer.join();
//    consumer.join();
//
//    SLog* pstLog = new SLog();
//    char* pszDir = "..";



    return 0;
}
