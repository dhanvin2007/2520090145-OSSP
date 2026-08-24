CODE 1
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int i;
    pid_t pid;
    int status;

    printf("Parent Process\n");
    printf("Parent PID: %d\n\n", getpid());

    for (i = 1; i <= 3; i++)
    {
        pid = fork();

        if (pid < 0)
        {
            perror("fork failed");
            exit(1);
        }

        if (pid == 0)
        {
            printf("Child %d: PID = %d, PPID = %d\n",
                   i, getpid(), getppid());

            sleep(i * 2);

            printf("Child %d terminating...\n", i);

            exit(i);
        }
    }

    for (i = 0; i < 3; i++)
    {
        pid = wait(&status);

        printf("Parent collected child PID: %d\n", pid);

        if (WIFEXITED(status))
        {
            printf("Exit status: %d\n\n",
                   WEXITSTATUS(status));
        }
    }

    printf("All children completed.\n");

    return 0;
}

