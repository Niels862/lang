#include "program.h"

Program *Program_new() {
    Program *pr = malloc(sizeof(Program));
    pr->code = NULL;
    pr->code_size = 0;
    pr->stack = DS_new();
    pr->ip = 0;
    pr->sp = 0;
    pr->bp = 0;
    return pr;
}

void Program_open(Program *pr, FILE *file) {
    unsigned int header_size, data_size;
    char *header;
    fread(&header_size, sizeof(unsigned int), 1, file);
    header = malloc(header_size * sizeof(char));
    fread(header, sizeof(char), header_size, file);
    data_size = *(int *)header;
    pr->code_size = *(int *)(header + 4);
    DS_expand(pr->stack, data_size);
    fread(pr->stack, sizeof(char), data_size, file);
    pr->code = malloc(pr->code_size * sizeof(char));
    fread(pr->code, sizeof(char), pr->code_size, file);
    free(header);
}

void Program_destruct(Program *pr) {
    if (pr->code != NULL) {
        free(pr->code);
    }
    DS_destruct(pr->stack);
    free(pr);
}
