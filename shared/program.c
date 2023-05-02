#include "program.h"

Program *Program_new() {
    Program *pr = malloc(sizeof(Program));
    pr->code = NULL;
    pr->stack = DS_new();
    pr->ip = 0;
    pr->sp = 0;
    pr->bp = 0;
    return pr;
}

void Program_open(Program *pr, FILE file) {
    
}

void Program_destruct(Program *pr) {
    if (pr->code != NULL) {
        free(pr->code);
    }
    DS_destruct(pr->stack);
    free(pr);
}
