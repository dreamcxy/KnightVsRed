//
// Created by cxy on 2022/6/24.
// 每一个客户端发过来的连接都会生成一个connection
//

#ifndef SERVER_CONNECTION_H
#define SERVER_CONNECTION_H


class CConnetion
{
public:
    CConnetion() {}
    ~CConnetion() {}

    void OnRecv();
    void OnWrite();
};

#endif //SERVER_CONNECTION_H
