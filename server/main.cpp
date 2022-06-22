// 其实是个测试程序
#include <iostream>
#include <cassert>
#include <thread>
#include "kfifo.h"

#define N ((1 << 20))
void Producer(KFIFO::STKFifo* pstFifo)
{
    int i = 0;
    while (i < N)
    {
        char buffer[20];
        snprintf(buffer, sizeof(buffer), "hello world :%d", i);
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
        KFIFO::KFifoGet(pstFifo, buffer, 20);
        std::cout << buffer << std::endl;
        i ++;
    }
};

int main()
{
    uint32_t size = 10;
    auto pstFifo = KFIFO::KFifoAlloc(10);
    if (pstFifo == nullptr)
    {
        assert(false);
        return -1;
    }

    std::thread producer(Producer, pstFifo);
    std::thread consumer(Consumer, pstFifo);

    producer.join();
    consumer.join();

    return 0;
}
