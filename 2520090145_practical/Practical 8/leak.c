#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *ptr;

    ptr = (int *)malloc(100 * sizeof(int));

    if (ptr == NULL)
    {
        printf("Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < 100; i++)
    {
        ptr[i] = i;
    }

    printf("Memory allocated successfully.\n");

    // free(ptr);  // Intentionally omitted

    return 0;
}
