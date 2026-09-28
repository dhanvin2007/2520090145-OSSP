#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t signal_received = 0;

void signal_handler(int sig) {

    if (sig == SIGINT) {
        printf("\nSIGINT received.\n");
        printf("Ctrl+C was pressed.\n");
    }
    else if (sig == SIGTERM) {
        printf("\nSIGTERM received.\n");
        printf("Termination request received.\n");
    }
    else if (sig == SIGUSR1) {
        printf("\nSIGUSR1 received.\n");
        printf("User-defined signal received.\n");
    }

    signal_received = sig;
}

int main() {

    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);
    signal(SIGUSR1, signal_handler);

    printf("Signal handling program started.\n");
    printf("Process ID: %d\n", getpid());
    printf("Waiting for signals...\n");

    while (1) {
        pause();

        if (signal_received == SIGTERM) {
            printf("Exiting program safely...\n");
            break;
        }

        signal_received = 0;
    }

    return 0;
}
