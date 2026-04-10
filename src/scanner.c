#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include "scanner.h"

int scan_directory(const char *folderPath, FileInfo *filesList)
{
    DIR *folder;
    struct dirent *file;
    struct stat fileData;
    int count = 0;

    folder = opendir(folderPath);

    if (folder == NULL)
    {
        printf("[ERROR] could not open folder: %s\n", folderPath);
        return 0;
    }

    file = readdir(folder);

    while (file != NULL)
    {
        int nameLength = strlen(file->d_name);

        if (nameLength > 4)
        {
            if (strcmp(file->d_name + nameLength - 4, ".txt") == 0)
            {
                char fullPath[200];

                sprintf(fullPath, "%s/%s", folderPath, file->d_name);

                if (stat(fullPath, &fileData) == 0)
                {
                    strcpy(filesList[count].filename, file->d_name);
                    filesList[count].size = fileData.st_size;
                    strcpy(filesList[count].timestamp, ctime(&fileData.st_mtime));
                    count++;
                }
            }
        }

        file = readdir(folder);
    }

    closedir(folder);

    return count;
}
