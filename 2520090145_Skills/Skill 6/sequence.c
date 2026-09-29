#include <stdio.h>
#include <string.h>

int main() {
    char input[200];

    printf("===== ESCAPE SEQUENCE TEST =====\n\n");

    printf("1. New line:\nHello\nUbuntu\n");

    printf("\n2. Tab:\nHello\tUbuntu\n");

    printf("\n3. Backslash: \\\n");

    printf("\n4. Double quote: \"Hello\"\n");

    printf("\n5. Single quote: 'Hello'\n");

    printf("\n6. Enter a command with escaped spaces:\n");
    printf("Example: Operating\\ Systems\\ Lab\n");

    printf("\nEnter a string: ");
    fgets(input, sizeof(input), stdin);

    input[strcspn(input, "\n")] = '\0';

    printf("\nParser Output:\n");
    printf("Original input: [%s]\n", input);
    printf("Length: %lu\n", strlen(input));

    printf("\nCharacters:\n");

    for (int i = 0; input[i] != '\0'; i++) {
        printf("Character %d: [%c]\n", i + 1, input[i]);
    }

    return 0;
}
