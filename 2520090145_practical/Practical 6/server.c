#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FIFO_NAME "server_fifo"
#define BUFFER_SIZE 200

int main() {
    char buffer[BUFFER_SIZE];

    // Create the named pipe
    mkfifo(FIFO_NAME, 0666);

    printf("Server started...\n");
    printf("Waiting for client messages...\n");

    while (1) {
        int fd = open(FIFO_NAME, O_RDONLY);

        if (fd == -1) {
            perror("open");
            exit(1);
        }

        int n = read(fd, buffer, BUFFER_SIZE - 1);
        close(fd);

        if (n > 0) {
            buffer[n] = '\0';

            printf("Client message: %s\n", buffer);

            // Process the message
            if (strcmp(buffer, "exit") == 0) {
                printf("Server shutting down...\n");
                break;
            }

            printf("Server response: Message received successfully.\n");
        }
    }

    unlink(FIFO_NAME);

    return 0;
}
