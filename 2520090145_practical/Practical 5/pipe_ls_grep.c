#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int pipefd[2];

    pid_t child1, child2;

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    /* First child process */
    child1 = fork();

    if (child1 < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child1 == 0)
    {
        /* Child 1: execute ls -l */

        close(pipefd[0]);

        dup2(pipefd[1], STDOUT_FILENO);

        close(pipefd[1]);

        execlp("ls", "ls", "-l", NULL);

        perror("execlp ls");
        exit(EXIT_FAILURE);
    }

    /* Second child process */
    child2 = fork();

    if (child2 < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child2 == 0)
    {
        /* Child 2: execute grep ".c" */

        close(pipefd[1]);

        dup2(pipefd[0], STDIN_FILENO);

        close(pipefd[0]);

        execlp("grep", "grep", ".c", NULL);

        perror("execlp grep");
        exit(EXIT_FAILURE);
    }

    /* Parent process */

    close(pipefd[0]);
    close(pipefd[1]);

    waitpid(child1, NULL, 0);
    waitpid(child2, NULL, 0);

    printf("Command execution completed.\n");

    return 0;
}
