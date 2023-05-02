#include "program.h"
#include <stdio.h>

int interpret(int argc, char *argv[]) {
    Program *pr = Program_new();

    Program_destruct(pr);
    return 0;
}

int main(int argc, char *argv[]) {
    return interpret(argc, argv);
}
