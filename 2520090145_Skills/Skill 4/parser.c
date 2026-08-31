#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKENS 50
#define MAX_LENGTH 100

/* Token structure */
typedef struct
{
    char value[MAX_LENGTH];
    char type[20];
} Token;

/* Parse tree structure */
typedef struct Node
{
    char value[MAX_LENGTH];
    struct Node *left;
    struct Node *right;
} Node;

/* Global token array */
Token tokens[MAX_TOKENS];
int token_count = 0;
int current = 0;


/* Create a new parse tree node */
Node *createNode(char *value)
{
    Node *newNode = (Node *)malloc(sizeof(Node));

    if (newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    strcpy(newNode->value, value);
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}


/* Tokenize the input */
void tokenize(char *input)
{
    int i = 0;

    token_count = 0;

    while (input[i] != '\0')
    {
        /* Ignore whitespace */
        if (isspace(input[i]))
        {
            i++;
            continue;
        }

        /* Identifier */
        if (isalpha(input[i]))
        {
            int j = 0;

            while (isalnum(input[i]))
            {
                if (j < MAX_LENGTH - 1)
                {
                    tokens[token_count].value[j++] = input[i];
                }

                i++;
            }

            tokens[token_count].value[j] = '\0';

            strcpy(tokens[token_count].type, "IDENTIFIER");

            token_count++;
        }

        /* Number */
        else if (isdigit(input[i]))
        {
            int j = 0;

            while (isdigit(input[i]))
            {
                if (j < MAX_LENGTH - 1)
                {
                    tokens[token_count].value[j++] = input[i];
                }

                i++;
            }

            tokens[token_count].value[j] = '\0';

            strcpy(tokens[token_count].type, "NUMBER");

            token_count++;
        }

        /* Operators and delimiters */
        else if (input[i] == '=' ||
                 input[i] == '+' ||
                 input[i] == '-' ||
                 input[i] == '*' ||
                 input[i] == '/')
        {
            tokens[token_count].value[0] = input[i];
            tokens[token_count].value[1] = '\0';

            strcpy(tokens[token_count].type, "OPERATOR");

            token_count++;

            i++;
        }

        /* Unknown character */
        else
        {
            printf("\nInvalid character found: %c\n", input[i]);

            i++;
        }

        /* Prevent token overflow */
        if (token_count >= MAX_TOKENS)
        {
            printf("Too many tokens!\n");
            break;
        }
    }
}


/* Display token stream */
void displayTokens()
{
    int i;

    printf("\n----- TOKEN STREAM -----\n");

    if (token_count == 0)
    {
        printf("No tokens found.\n");
        return;
    }

    for (i = 0; i < token_count; i++)
    {
        printf("Token %d: %-10s Type: %s\n",
               i + 1,
               tokens[i].value,
               tokens[i].type);
    }
}


/* Parser */
Node *parse()
{
    Node *root;

    /* Empty command */
    if (token_count == 0)
    {
        printf("\nEmpty command. Nothing to parse.\n");
        return NULL;
    }

    /* Check identifier */
    if (current >= token_count ||
        strcmp(tokens[current].type, "IDENTIFIER") != 0)
    {
        printf("\nSyntax Error: Expected identifier.\n");
        return NULL;
    }

    root = createNode("ASSIGNMENT");

    root->left = createNode(tokens[current].value);

    current++;


    /* Check equal sign */
    if (current >= token_count ||
        strcmp(tokens[current].value, "=") != 0)
    {
        printf("\nSyntax Error: Expected '='.\n");

        free(root->left);
        free(root);

        return NULL;
    }

    current++;


    /* Check number */
    if (current >= token_count ||
        strcmp(tokens[current].type, "NUMBER") != 0)
    {
        printf("\nSyntax Error: Expected number.\n");

        free(root->left);
        free(root);

        return NULL;
    }

    root->right = createNode(tokens[current].value);

    current++;


    /* Check for extra tokens */
    if (current < token_count)
    {
        printf("\nSyntax Error: Unexpected token '%s'.\n",
               tokens[current].value);

        free(root->left);
        free(root->right);
        free(root);

        return NULL;
    }

    return root;
}


/* Display parse tree */
void displayTree(Node *root, int level)
{
    int i;

    if (root == NULL)
        return;

    for (i = 0; i < level; i++)
    {
        printf("  ");
    }

    printf("|-- %s\n", root->value);

    displayTree(root->left, level + 1);

    displayTree(root->right, level + 1);
}


/* Free parse tree memory */
void freeTree(Node *root)
{
    if (root == NULL)
        return;

    freeTree(root->left);

    freeTree(root->right);

    free(root);
}


/* Main function */
int main()
{
    char input[500];

    printf("=====================================\n");
    printf("       SIMPLE COMMAND PARSER\n");
    printf("=====================================\n");

    printf("Type 'exit' to quit the parser.\n");


    while (1)
    {
        printf("\nEnter command: ");

        /* Read input */
        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            break;
        }

        /* Remove newline */
        input[strcspn(input, "\n")] = '\0';


        /* Exit command */
        if (strcmp(input, "exit") == 0)
        {
            printf("Exiting parser...\n");
            break;
        }


        /* Split input into tokens */
        tokenize(input);


        /* Display tokens */
        displayTokens();


        /* Start parsing */
        current = 0;

        Node *parseTree = parse();


        /* If syntax is correct */
        if (parseTree != NULL)
        {
            printf("\n----- PARSE TREE -----\n");

            displayTree(parseTree, 0);


            printf("\n----- EXECUTION STRUCTURE -----\n");

            printf("Operation : ASSIGNMENT\n");

            printf("Variable  : %s\n",
                   parseTree->left->value);

            printf("Value     : %s\n",
                   parseTree->right->value);


            printf("\nSyntax validation successful!\n");


            /* Release memory */
            freeTree(parseTree);
        }
    }


    return 0;
}
