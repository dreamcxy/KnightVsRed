//
// Created by cxy on 2022/8/7.
// 操作文件要用的一些函数, 提取出来是为了以后可能会做的多平台
//

#ifndef KNIGHTVSREDSERVER_FILEUTILS_H
#define KNIGHTVSREDSERVER_FILEUTILS_H

#include <cstdint>
#include <vector>
#include <string.h>
#include <string>

namespace FileUtils
{

    // 获取文件大小
    long GetFileSize(const char* pszFilePath);

    // 同目录下重命名文件
    void RenameFileSameDir(const char* pszDirName, const char* pszOldFileName, const char* pszNewFileName);

    // 获取当前目录下面以prefix前缀的文件
    std::vector<std::string> GetFilesInDir(const char* pszDirName, const char* pszFilePrefix);

    // 获取当前目录下面以prefix前缀的最新的文件
    std::string GetLatestFileInDir(const char* pszDirName, const char* pszFilePrefix);

    // string类型的字符串的分割

}


#endif //KNIGHTVSREDSERVER_FILEUTILS_H
