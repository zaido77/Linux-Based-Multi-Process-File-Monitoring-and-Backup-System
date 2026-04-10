#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "signal_handler.h"

extern int pfds[2];

void handle_sigint(int sig) {
    printf("\n[CTRL+C] Exiting System ...\n");
    close(pfds[0]);
    close(pfds[1]);
    exit(0);
}
