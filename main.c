#include "lexer.h"
#include "parser.h"
#include "linkedlist.h"
#include "hashmap.h"
#include "utils.h"
#include <stdio.h>

int compile(int argc, char *argv[]) {
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
    LL_print(tokens, Token_print);

    if (parser(tokens)) {
        return 1;
    }

    LL_destruct(tokens, Token_destruct);
    fclose(file);
    return 0;
}

int main(int argc, char *argv[]) {
    char str[3];
    int i;
    str[2] = '\0';
    HashMap *hashmap = HM_new(hash_string, comp_string);
    for (i = 0; i < 100; i++) {
        str[0] = 0x30 + i / 10;
        str[1] = 0x30 + i % 10;
        HM_add_string(hashmap, str);
    }
    HM_remove(hashmap, "20", free);
    HM_destruct(hashmap, free);
    return 0;
}
