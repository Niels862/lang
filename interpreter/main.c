#include "program.h"
#include <stdio.h>

int interpret(int argc, char *argv[]) {
    Program *pr;
    FILE *file;
    if (argc < 2) {
        printf("Expected filename\n");
        return 1;
    }
    file = fopen(argv[1], "rb");
    if (file == NULL) {
        printf("Could not open file\n");
    }
    pr = Program_new();
    Program_open(pr, file);
    fclose(file);
    Program_destruct(pr);
    return 0;
}

int main(int argc, char *argv[]) {
    return interpret(argc, argv);
}
