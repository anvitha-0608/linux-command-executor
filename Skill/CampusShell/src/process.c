#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include "../include/process.h"

// ---------- Part A: Command Execution ----------

void executeCommand()
{
    char command[256];
    char *args[20];
    int i = 0;

    printf("Enter Linux command (e.g. ls, pwd, date): ");
    scanf(" %[^\n]", command);

    char *token = strtok(command, " ");
    while (token != NULL)
    {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;

    pid_t pid = fork();

    if (pid < 0)
    {
        printf("Fork failed.\n");
        return;
    }
    else if (pid == 0)
    {
        execvp(args[0], args);
        printf("Command not found: %s\n", args[0]);
        exit(1);
    }
    else
    {
        wait(NULL);
    }
}

// ---------- Part B: Process Management ----------

void showPID()
{
    printf("Current Process ID (PID): %d\n", getpid());
}

void showPPID()
{
    printf("Parent Process ID (PPID): %d\n", getppid());
}

void showRunningProcesses()
{
    pid_t pid = fork();

    if (pid == 0)
    {
        char *args[] = {"ps", "-ef", NULL};
        execvp("ps", args);
        exit(1);
    }
    else
    {
        wait(NULL);
    }
}

void killProcess()
{
    int pid;
    printf("Enter PID to kill: ");
    scanf("%d", &pid);

    if (kill(pid, SIGKILL) == 0)
        printf("Process %d killed.\n", pid);
    else
        printf("Failed to kill process %d.\n", pid);
}

void processMenu()
{
    int choice;

    printf("\n----- Process Management -----\n");
    printf("1. Show PID\n");
    printf("2. Show Parent PID\n");
    printf("3. Show Running Processes\n");
    printf("4. Kill Process\n");
    printf("5. Back\n");
    printf("Enter Choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
        case 1: showPID(); break;
        case 2: showPPID(); break;
        case 3: showRunningProcesses(); break;
        case 4: killProcess(); break;
        case 5: return;
        default: printf("Invalid choice.\n");
    }
}
