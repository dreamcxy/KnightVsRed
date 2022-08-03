//
// Created by chenxiaoyu5 on 2022/7/27.
//

#ifndef SERVER_FILERAII_H
#define SERVER_FILERAII_H


#include <fstream>
#include <sys/stat.h>
#include "unistd.h"
#include "commondefine.h"

class CFileRaii
{
public:
    CFileRaii() = default;
    CFileRaii(const char* pszDir, const char* pszFileName)
    {
        if (access(pszDir, 0) == -1)
        {
            mkdir(pszDir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        }
        char szFilePath[MAX_LOG_FILE_DIR_PREFIX_SIZE * 2];
        sprintf(szFilePath, "%s/%s", pszDir, pszFileName);
        m_oOutFile.open(szFilePath,  std::ios::app | std::ios::out);
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
