//
// Created by chenxiaoyu5 on 2022/8/17.
//


#include "include/homeserver.h"


int main(int argc,char *argv[])
{
    CHomeServer* poSvr = new CHomeServer();
    poSvr->Run(argc, argv);
    return 0;
}