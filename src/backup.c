#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "backup.h"

#define BACKUP_DIR "backup"
#define FILE_CHUNK_SIZE 4096

void backup_file(const char *sourceDir, const char *filename) {
    char sourcePath[256];
    char destPath[256];

    snprintf(sourcePath, sizeof(sourcePath), "%s/%s", sourceDir, filename);
    snprintf(destPath, sizeof(destPath), "%s/%s", BACKUP_DIR, filename);

    FILE *src = fopen(sourcePath, "rb");
    if (src == NULL) {
        printf("[ERROR] File not found: %s\n", sourcePath);
        return;
    }

    fseek(src, 0, SEEK_END);
    long fileSize = ftell(src);
    rewind(src);

    if (fileSize == 0) {
        printf("[WARNING] File is empty, skipping: %s\n", filename);
        fclose(src);
        return;
    }

    FILE *dst = fopen(destPath, "wb");
    if (dst == NULL) {
        printf("[ERROR] Could not create backup file: %s\n", destPath);
        fclose(src);
        return;
    }

    char srcFileContent[FILE_CHUNK_SIZE];
    size_t numberOfBytes;

    while ((numberOfBytes = fread(srcFileContent, 1, FILE_CHUNK_SIZE, src)) > 0) {
        fwrite(srcFileContent, 1, numberOfBytes, dst);
    }

    fclose(src);
    fclose(dst);

    printf("[SUCCESS] File copied: %s -> %s\n", sourcePath, destPath);
}

int main() {

    char folder[] = "filesToScan";

    printf("=== Backup Module Test ===\n\n");

    printf("Test 1: Normal file\n");
    backup_file(folder, "file1.txt");

    printf("\nTest 2: File that does not exist\n");
    backup_file(folder, "file4.txt");

    printf("\nTest 3: Empty file\n");
    backup_file(folder, "empty.txt");

    printf("\n=== Done ===\n");
    return 0;
}
