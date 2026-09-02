#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>

int main()
{
    int pipefd[2];
    pid_t pid;

    char buffer[100];
    int data[] = {10, 20, 30, 40, 50};
    int n = 5;

    struct timespec start, end;

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid > 0)
    {
        /* Parent - Producer */

        close(pipefd[0]);

        printf("----- PRODUCER (PARENT) -----\n");
        printf("Parent PID: %d\n", getpid());

        clock_gettime(CLOCK_MONOTONIC, &start);

        for (int i = 0; i < n; i++)
        {
            write(pipefd[1], &data[i], sizeof(data[i]));
            printf("Produced: %d\n", data[i]);
        }

        close(pipefd[1]);

        wait(NULL);

        clock_gettime(CLOCK_MONOTONIC, &end);

        double time_taken =
            (end.tv_sec - start.tv_sec) +
            (end.tv_nsec - start.tv_nsec) / 1e9;

        printf("\nCommunication completed.\n");
        printf("Communication time: %.6f seconds\n", time_taken);
    }
    else
    {
        /* Child - Consumer */

        close(pipefd[1]);

        printf("\n----- CONSUMER (CHILD) -----\n");
        printf("Child PID: %d\n", getpid());

        while (read(pipefd[0], buffer, sizeof(int)) > 0)
        {
            int value;
            memcpy(&value, buffer, sizeof(int));

            printf("Consumed: %d\n", value);
        }

        close(pipefd[0]);

        printf("Consumer finished.\n");

        exit(0);
    }

    return 0;
}
