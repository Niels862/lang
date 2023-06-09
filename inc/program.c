#include "program.h"
#include "operation.h"
#include <stdint.h>

Program *Program_new() {
    Program *pr = malloc(sizeof(Program));
    pr->code = NULL;
    pr->code_size = 0;
    pr->stack = DS_new();
    pr->ip = 0;
    pr->bp = 0;
    return pr;
}

void Program_open(Program *pr, FILE *file) {
    uint32_t header_size, data_size;
    void *header;

    fread(&header_size, 4, 1, file);
    header = malloc(header_size);
    fread(header, 1, header_size, file);

    data_size = *(uint32_t *)header;
    pr->code_size = *(uint32_t *)(header + 4);

    DS_expand(pr->stack, data_size);
    fread(pr->stack->data, 1, data_size, file);
    pr->stack->top += data_size;

    pr->code = malloc(pr->code_size);
    fread(pr->code, 1, pr->code_size, file);

    free(header);
}

void Program_execute(Program *pr) {
    Operation const *op;
    if (pr->code == NULL) {
        return;
    }
    while (pr->ip < pr->code_size) {
        DS_print(pr->stack, 16);
        op = &operations[pr->code[pr->ip]];
        op->func(pr);
        if (op->size > 0) {
            pr->ip += op->size;
        }
    }
}

void Program_destruct(Program *pr) {
    if (pr->code != NULL) {
        free(pr->code);
    }
    DS_destruct(pr->stack);
    free(pr);
}
