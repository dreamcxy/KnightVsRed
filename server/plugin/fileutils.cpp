//
// Created by 15850 on 2022/8/7.
//

#include "fileutils.h"
#include "commondefine.h"
#include <sys/stat.h>
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

void FileUtils::GetLatestFileInDir(const char *pszDirName, const char *pszFilePrefix)
{
    dirent* dirent;

}