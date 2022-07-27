//
// Created by chenxiaoyu5 on 2022/7/27.
//

#ifndef SERVER_FILERAII_H
#define SERVER_FILERAII_H


#include <fstream>
#include <sys/stat.h>
#include "unistd.h"

class CFileRaii
{
public:
    CFileRaii() = default;
    CFileRaii(const char* pszDir, const char* pszFilePath)
    {
        if (access(pszDir, 0) == -1)
        {
            mkdir(pszDir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        }
        m_oOutFile.open(pszFilePath,  std::ios::app | std::ios::out);

    }

    ~CFileRaii() { m_oOutFile.close(); }

    CFileRaii(CFileRaii const&) = delete;
    CFileRaii& operator= (CFileRaii const &) = delete;

    void write(const char* pszContent)
    {
        m_oOutFile << pszContent << "\n";
    }

private:
    std::ofstream m_oOutFile;
};



#endif //SERVER_FILERAII_H
