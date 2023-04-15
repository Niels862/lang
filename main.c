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
    int *p;
    str[2] = '\0';
    HashMap *hashmap = HM_new(hash_string, comp_string, free, free);
    for (i = 0; i < 100; i++) {
        str[0] = 0x30 + i / 10;
        str[1] = 0x30 + i % 10;
        p = malloc(sizeof(int));
        *p = 10 * i;
        HM_add_string(hashmap, str, p);
    }
    printf("%d\n", *((int *)HM_get(hashmap, "42")));
    HM_destruct(hashmap);
    return 0;
}
