//
// Created by chenxiaoyu5 on 2022/6/23.
//

#ifndef SERVER_COMMONDEFINE_H
#define SERVER_COMMONDEFINE_H


#include <cstdint>
#include <string>
#include "magic_enum.h"

// 网络连接对应的ip:port
struct STAddressConfig
{
    std::string m_strIP;
    int32_t     m_nPort;
};

// listensocket最大监听数目
#define MAX_LISTEN_SOCK_QUEUE (1024)

// epoll 监听的最大事件数目
#define MAX_EVENT_LISTEN_NUM (100000)


// 日志buffer最大
#define MAX_LOG_BUFFER_SIZE (1024 * 1024)
// 日志目录和文件名最大长度
#define MAX_LOG_FILE_DIR_PREFIX_SIZE (10)

// 默认日志目录名字
#define DEFAULT_LOG_DIR "log"


// 日志等级
//enum E_LOG_LEVEL
//{
//    INFO = 0,
//    WARN,
//    ERROR
//};

ENUM_MACRO(E_LOG_LEVEL, E_INFO, E_WARN, E_ERROR);


#endif //SERVER_COMMONDEFINE_H

