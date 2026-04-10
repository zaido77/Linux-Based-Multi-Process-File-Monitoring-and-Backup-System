#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>
#include "signal_handler.h"
#include "alerts_logger.h"
#include "logger.h"
#include "scanner.h"
#include "backup.h"
#include <time.h>
#include "FileInfoStruct.h"

int pfds[2];

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("[WARNING] Follow this to compile correctly: %s <directory_path>\n", argv[0]);
        return 1;
    }

    // --- START MESSAGE ---
    time_t now = time(NULL);
    char *start_time = ctime(&now);
    start_time[strlen(start_time) - 1] = '\0'; // Remove \n from ctime

    printf("------------------------------------------------\n");
    printf("Running Monitor System on [%s]\n", argv[1]);
    printf("[%s]\n", start_time);
    printf("------------------------------------------------\n");
    fflush(stdout);

    signal(SIGINT, handle_sigint);

    if (pipe(pfds) == -1)
    {
        log_alert("[ERROR] Pipe creation failed");
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0)
    {
        log_alert("[ERROR] Fork failed");
        return 1;
    }

    if (pid > 0)
    {
	// --- PARENT PROCESS ---

        close(pfds[0]); // close unused read end

        FileInfo *files = malloc(15 * sizeof(FileInfo));;
        int filesCount = scan_directory(argv[1], files);

        if (filesCount > 0)
        {
            for (int i = 0; i < filesCount; i++)
            {
                FileInfo fileInfoToSend = files[i];

                char msg[256];
                snprintf(msg, sizeof(msg), "[Parent] Sending file info: %s", fileInfoToSend.filename);
                log_alert(msg);

		backup_file(argv[1], files[i].filename);

                write(pfds[1], &fileInfoToSend, sizeof(FileInfo));
            }
            free(files);
        }

        close(pfds[1]);
        wait(NULL);
        log_alert("[Parent] All files sent. Parent process exiting.");
    }
    else
    {
	// --- CHILD PROCESS ---

        close(pfds[1]); // close unused write end

        FileInfo receivedFileInfo;
        while (read(pfds[0], &receivedFileInfo, sizeof(FileInfo)) > 0)
        {
            char msg[256];
            snprintf(msg, sizeof(msg), "[Child] Received file: %s (%ld bytes)",
                     receivedFileInfo.filename, receivedFileInfo.size);
            log_alert(msg);

            log_file_info(receivedFileInfo);
        }

        close(pfds[0]);
        log_alert("[Child] All files received. Child process exiting.");
    }


    // --- END MESSAGE ---
    if (pid > 0)
    {
        printf("------------------------------------------------\n");
        printf("End of System\n");
        printf("------------------------------------------------\n");
    }

    return 0;
}
