#ifndef FILEINFOSTRUCT_H
#define FILEINFOSTRUCT_H

typedef struct {
    char filename[100];
    long size;
    char timestamp[50];
} FileInfo;

#endif
