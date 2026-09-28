#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Global variable
int global_var = 100;

// Static global variable
static int static_var = 200;

// Uninitialized variables - BSS
int uninitialized_global;
static int uninitialized_static;

// Function - Code/Text segment
void show_code_address()
{
    printf("Address of function (Code):       %p\n",
           (void *)show_code_address);
}

int main()
{
    // Stack variable
    int stack_var = 300;

    // Static local variable
    static int static_local_var = 400;

    // Heap variable
    int *heap_var = (int *)malloc(sizeof(int));

    if (heap_var == NULL)
    {
        printf("Memory allocation failed\n");
        return 1;
    }

    *heap_var = 500;

    printf("\n========== MEMORY ADDRESS LAYOUT ==========\n");

    show_code_address();

    printf("Address of global variable:        %p\n",
           (void *)&global_var);

    printf("Address of static variable:        %p\n",
           (void *)&static_var);

    printf("Address of BSS global variable:    %p\n",
           (void *)&uninitialized_global);

    printf("Address of BSS static variable:    %p\n",
           (void *)&uninitialized_static);

    printf("Address of static local variable:  %p\n",
           (void *)&static_local_var);

    printf("Address of heap variable:          %p\n",
           (void *)heap_var);

    printf("Address of stack variable:         %p\n",
           (void *)&stack_var);

    printf("\nProcess ID (PID): %d\n", getpid());

    printf("\nProgram will run for 60 seconds...\n");
    printf("Use another terminal to check /proc/<PID>/maps\n");

    sleep(60);

    free(heap_var);

    return 0;
}
