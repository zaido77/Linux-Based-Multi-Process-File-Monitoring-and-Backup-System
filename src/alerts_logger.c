#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void log_alert(const char *message)
{
    char logfile[] = "alerts/alerts.log";

    FILE *fp = fopen(logfile, "a");
    if (!fp)
    {
        printf("[ERROR] Could not open log file: %s\n", logfile);
        return;
    }

    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    char timeStr[64];
    strftime(timeStr, sizeof(timeStr), "%d/%m/%Y %H:%M:%S", t);

    fprintf(fp, "[%s] %s\n", timeStr, message);
    printf("%s\n", message);

    fclose(fp);
}
