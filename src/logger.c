#include <stdio.h>
#include <string.h>
#include "FileInfoStruct.h"
#include "logger.h"

void log_file_info(FileInfo fileInfo)
{
    FILE *fp = fopen("logs/report.txt", "a");

    if (fp == NULL)
    {
        printf("[ERROR] opening report.txt file failed\n");
        return;
    }

    fprintf(fp, "File: %s | Size: %ld bytes | Timestamp: %s\n", 
        fileInfo.filename, fileInfo.size, fileInfo.timestamp);

    fclose(fp);
}
