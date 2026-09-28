#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define SIZE 1000000

int main()
{
    int *data;
    pid_t pid;

    printf("Parent PID: %d\n", getpid());

    // Allocate memory before fork()
    data = (int *)malloc(SIZE * sizeof(int));

    if (data == NULL)
    {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Initialize data
    for (int i = 0; i < SIZE; i++)
    {
        data[i] = i;
    }

    printf("Memory allocated and initialized.\n");
    printf("Address of data: %p\n", (void *)data);

    printf("\nPress Enter before fork...");
    getchar();

    pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        free(data);
        return 1;
    }

    if (pid == 0)
    {
        // Child process
        printf("\n===== CHILD PROCESS =====\n");
        printf("Child PID: %d\n", getpid());
        printf("Parent PID: %d\n", getppid());
        printf("Address of data in child: %p\n", (void *)data);

        printf("Before modification: data[0] = %d\n", data[0]);

        printf("\nChild is modifying data...\n");

        // Modify memory in child
        data[0] = 9999;

        printf("After modification: data[0] = %d\n", data[0]);

        printf("Child sleeping for 10 seconds...\n");
        sleep(10);

        free(data);
        exit(0);
    }
    else
    {
        // Parent process
        printf("\n===== PARENT PROCESS =====\n");
        printf("Parent PID: %d\n", getpid());
        printf("Child PID: %d\n", pid);
        printf("Address of data in parent: %p\n", (void *)data);

        printf("Parent sees data[0] = %d\n", data[0]);

        printf("Parent sleeping for 10 seconds...\n");
        sleep(10);

        printf("\nAfter child modification:\n");
        printf("Parent still sees data[0] = %d\n", data[0]);

        wait(NULL);

        free(data);
    }

    return 0;
}
