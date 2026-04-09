#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "backup.h"

#define BACKUP_DIR  "backup"
#define FILE_CHUNK_SIZE 4096

void backup_file(const char *sourceDir, const char *filename) {
    int sourceLen = strlen(sourceDir) + strlen(filename) + 2; // +1 for '/', +1 for '\0'
    int destLen   = strlen(BACKUP_DIR) + strlen(filename) + 2;

    char *sourcePath = (char *)malloc(sourceLen);
    char *destPath   = (char *)malloc(destLen);

    if (sourcePath == NULL || destPath == NULL) {
        printf("[ERROR] Memory allocation failed\n");
        return;
    }

    snprintf(sourcePath, sourceLen, "%s/%s", sourceDir, filename);
    snprintf(destPath, destLen, "%s/%s", BACKUP_DIR, filename);

    FILE *srcFile = fopen(sourcePath, "rb");
    if (srcFile == NULL) {
        printf("[ERROR] File not found: %s\n", sourcePath);
        free(sourcePath);
        free(destPath);
        return;
    }

    fseek(srcFile, 0, SEEK_END);
    long fileSize = ftell(srcFile);
    rewind(srcFile);

    if (fileSize == 0) {
        printf("[WARNING] File is empty, skipping: %s\n", filename);
        fclose(srcFile);
        free(sourcePath);
        free(destPath);
        return;
    }

    FILE *destFile = fopen(destPath, "wb");
    if (destFile == NULL) {
        printf("[ERROR] Could not create backup file: %s\n", destPath);
        fclose(srcFile);
        free(sourcePath);
        free(destPath);
        return;
    }

    char srcFileContent[FILE_CHUNK_SIZE];
    size_t numberOfBytes;

    while ((numberOfBytes = fread(srcFileContent, 1, FILE_CHUNK_SIZE, srcFile)) > 0) {
        fwrite(srcFileContent, 1, numberOfBytes, destFile);
    }

    fclose(srcFile);
    fclose(destFile);

    printf("[SUCCESS] File copied: %s -> %s\n", sourcePath, destPath);

    free(sourcePath);
    free(destPath);
}
