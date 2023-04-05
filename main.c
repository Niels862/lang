#include "lexer.h"
#include "parser.h"
#include "linkedlist.h"
#include "tree.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    FILE *file;
    LinkedList *tokens;
    if (argc > 1) {
        file = fopen(argv[1], "rb");
    } else {
        file = fopen("hello-world.txt", "rb");
    }
    if (file == NULL) {
        printf("Could not open file\n");
        return 1;
    }
    tokens = LL_new();
    lexer(file, tokens);
    LL_print(tokens, print_token);

    parser(tokens);

    LL_destruct(tokens, destruct_token);
    fclose(file);
    return 0;
}
