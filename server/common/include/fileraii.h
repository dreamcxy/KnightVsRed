//
// Created by chenxiaoyu5 on 2022/7/27.
//

#ifndef SERVER_FILERAII_H
#define SERVER_FILERAII_H


#include <fstream>
#include "dirent.h"
#include <io.h>

class FileRaii
{
public:
    FileRaii(const char* pszDir, const char* pszFilePath)
    {
        if (_access(pszDir, 0) == -1)
        {
            _mkdir(pszDir);
        }
        m_oOutFile.open(pszFilePath,  std::ios::app | std::ios::out);

    }

    ~FileRaii() { m_oOutFile.close(); }

    FileRaii(FileRaii const&) = delete;
    FileRaii& operator= (FileRaii const &) = delete;

    void write(const char* pszContent)
    {
        m_oOutFile << pszContent << "\n";
    }

private:
    std::ofstream m_oOutFile;
};



#endif //SERVER_FILERAII_H
