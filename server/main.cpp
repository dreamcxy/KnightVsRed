// 其实是个测试程序
#include <iostream>
#include <cassert>
#include <thread>
#include <fstream>
#include "common/include/fileraii.h"
#include "common/include/raii.h"
//#include "kfifo.h"
//#include "common/include/logger.h"

#define N ((1 << 20))
//void Producer(KFIFO::STKFifo* pstFifo)
//{
//    int i = 0;
//    while (i < N)
//    {
//        char buffer[20];
//        snprintf(buffer, sizeof(buffer), "hello world");
//        KFIFO::KFifoPut(pstFifo, buffer, sizeof(buffer));
//        i++;
//    }
//}
//
//void Consumer(KFIFO::STKFifo* pstFifo)
//{
//    int i = 0;
//    while (i < N)
//    {
//        char buffer[20];
//        KFIFO::KFifoGet(pstFifo, buffer, 11);
//        std::cout << buffer << std::endl;
//        i ++;
//    }
//};
using namespace std;

// 测试raii管理file
void test_fileraii();
// 测试通用的raii管理类
void test_commonraii();

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

//    test_fileraii();

    test_commonraii();
    return 0;
}
///////////////////////////////// 测试区域 ///////////////////////////////////////////
void test_fileraii()
{
    // 通过
    CFileRaii cFileRaii("log", "log/test_log.txt");
    cFileRaii.write("hello world");
    cFileRaii.write("plog");
}

void test_commonraii()
{
    std::ofstream file("log/test_log.txt");
    CRAIIManager file_raii([&file]()
    {
        if (file.is_open())  file.close();
    });
    file << "manager";
}