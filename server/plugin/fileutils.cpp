//
// Created by cxy on 2022/8/7.
//

#include "fileutils.h"
#include "commondefine.h"
#include <sys/stat.h>
#include <string.h>
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

std::vector<char*> FileUtils::GetFilesInDir(const char *pszDirName, const char *pszFilePrefix)
{
    dirent* diread;
    DIR *dir;
    std::vector<char* > vecFiles;
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
            vecFiles.push_back(diread->d_name);
        }
        closedir(dir);
    }
    else
    {
        perror("open dir fail");
    }
    return std::move(vecFiles);
}

