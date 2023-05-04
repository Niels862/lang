#include "program.h"
#include "datastack.h"
#include "utils.h"
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
    print_datablock(pr->code, pr->code_size, 16);
    Program_execute(pr);
    DS_print(pr->stack, 16);
    Program_destruct(pr);
    return 0;
}

int main(int argc, char *argv[]) {
    return interpret(argc, argv);
}
