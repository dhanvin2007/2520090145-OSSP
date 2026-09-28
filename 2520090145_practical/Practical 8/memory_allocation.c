#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i;

    printf("===== malloc() demonstration =====\n");

    int *a = (int *)malloc(5 * sizeof(int));

    if (a == NULL)
    {
        printf("malloc failed\n");
        return 1;
    }

    for (i = 0; i < 5; i++)
    {
        a[i] = (i + 1) * 10;
    }

    printf("Values allocated using malloc:\n");

    for (i = 0; i < 5; i++)
    {
        printf("%d ", a[i]);
    }

    printf("\n\n");

    printf("===== calloc() demonstration =====\n");

    int *b = (int *)calloc(5, sizeof(int));

    if (b == NULL)
    {
        printf("calloc failed\n");
        free(a);
        return 1;
    }

    printf("Values allocated using calloc:\n");

    for (i = 0; i < 5; i++)
    {
        printf("%d ", b[i]);
    }

    printf("\n\n");

    printf("===== realloc() demonstration =====\n");

    a = (int *)realloc(a, 10 * sizeof(int));

    if (a == NULL)
    {
        printf("realloc failed\n");
        free(b);
        return 1;
    }

    for (i = 5; i < 10; i++)
    {
        a[i] = (i + 1) * 10;
    }

    printf("Values after realloc:\n");

    for (i = 0; i < 10; i++)
    {
        printf("%d ", a[i]);
    }

    printf("\n\n");

    printf("===== free() demonstration =====\n");

    free(a);
    free(b);

    printf("Memory successfully released using free().\n");

    return 0;
}
