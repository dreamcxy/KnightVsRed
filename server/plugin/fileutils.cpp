//
// Created by cxy on 2022/8/7.
//

#include "fileutils.h"
#include "commondefine.h"
#include <sys/stat.h>
#include <functional>
#include <algorithm>
#include <cstring>
#include "dirent.h"

long FileUtils::GetFileSize(const char *pszFilePath)
{
    struct stat sb{};
    if (stat(pszFilePath, &sb) == -1)
    {
        // 可能由于文件不存在
        return 0;
    }
    return sb.st_size;
}

void FileUtils::RenameFileSameDir(const char *pszDirName, const char *pszOldFileName, const char *pszNewFileName)
{
    char szOldFilePath[MAX_LOG_FILE_PATH_SIZE];
    sprintf(szOldFilePath, "%s/%s", pszDirName, pszOldFileName);
    char szNewFilePath[MAX_LOG_FILE_PATH_SIZE];
    sprintf(szNewFilePath, "%s/%s", pszDirName, pszNewFileName);
    rename(szOldFilePath, szNewFilePath);
}

std::vector<std::string> FileUtils::GetFilesInDir(const char *pszDirName, const char *pszFilePrefix)
{
    dirent* diread;
    DIR *dir;
    std::vector<std::string > vecFiles;
    if ((dir = opendir(pszDirName)) != nullptr)
    {
        while ((diread = readdir(dir)) != nullptr)
        {
            if (strcmp(diread->d_name, ".") == 0 || strcmp(diread->d_name, "..") == 0)
            {
                continue;
            }
            if (pszFilePrefix != nullptr)
            {
                // 判断文件前缀是否跟pszFilePrefix相同
                if (strstr(diread->d_name, pszFilePrefix) == nullptr)
                {
                    continue;
                }
            }
            char szFilePath[strlen(pszDirName) + strlen(diread->d_name)];
            sprintf(szFilePath, "%s/%s", pszDirName, diread->d_name);
            std::string strFilePath(szFilePath);
            vecFiles.push_back(strFilePath.c_str());
        }
        closedir(dir);
    }
    else
    {
        perror("open dir fail");
    }
    return std::move(vecFiles);
}

std::string FileUtils::GetLatestFileInDir(const char *pszDirName, const char *pszFilePrefix)
{
    std::vector<std::string> && vecFiles = GetFilesInDir(pszDirName, pszFilePrefix);
    if (vecFiles.size() <= 0)
    {
        return nullptr;
    }
    if (vecFiles.size() == 1)
    {
        return vecFiles[0].c_str();
    }
    std::function<bool(std::string , std::string )> oFileSortByMtime = [](std::string  strFilePath1,  std::string  strFilePath2) -> bool
    {
        struct stat sb1;
        struct stat sb2;
        stat(strFilePath1.c_str(), &sb1);
        stat(strFilePath2.c_str(), &sb2);
        return sb1.st_mtim.tv_sec > sb2.st_mtim.tv_sec;
    };
    std::sort(vecFiles.begin(), vecFiles.end(), oFileSortByMtime);
    return vecFiles[0];
}

