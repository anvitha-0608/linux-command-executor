#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "../include/login.h"

void showLoginInfo()
{
    char cwd[1024];
    char hostname[256];
    time_t now;

    printf("\n----- Login Information -----\n");

    // Current user
    printf("User        : %s\n", getlogin());

    // Current working directory
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("Directory   : %s\n", cwd);

    // Hostname
    gethostname(hostname, sizeof(hostname));
    printf("Hostname    : %s\n", hostname);

    // Current time
    time(&now);
    printf("Time        : %s", ctime(&now));
}
