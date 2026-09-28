#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define FIFO_NAME "server_fifo"
#define BUFFER_SIZE 200

int main() {
    char message[BUFFER_SIZE];

    printf("Enter message: ");
    fgets(message, BUFFER_SIZE, stdin);

    message[strcspn(message, "\n")] = '\0';

    int fd = open(FIFO_NAME, O_WRONLY);

    if (fd == -1) {
        perror("open");
        exit(1);
    }

    write(fd, message, strlen(message) + 1);

    close(fd);

    printf("Message sent to server.\n");

    return 0;
}
