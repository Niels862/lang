#include "lexer.h"
#include "parser.h"
#include "linkedlist.h"
#include "hashmap.h"
#include "utils.h"
#include <stdio.h>

int compile(int argc, char *argv[]) {
    FILE *file;
    LinkedList *tokens;
    if (argc < 2) {
        printf("Expected filename\n");
        return 1;
    }
    file = fopen(argv[1], "rb");
    if (file == NULL) {
        printf("Could not open file\n");
        return 1;
    }
    tokens = LL_new();
    lexer(file, tokens);
    LL_print(tokens, Token_print);

    if (parser(tokens)) {
        return 1;
    }

    LL_destruct(tokens, Token_destruct);
    fclose(file);
    return 0;
}

int main(int argc, char *argv[]) {
    return compile(argc, argv);
}
