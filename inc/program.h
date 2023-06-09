#include "datastack.h"
#include <stdio.h>

#ifndef PROGRAM_H
#define PROGRAM_H

typedef struct {
    unsigned char *code;
    size_t code_size;
    DataStack *stack;
    uint32_t ip;
    uint32_t bp;
} Program;

Program *Program_new();
void Program_open(Program *pr, FILE *file);
void Program_execute(Program *pr);
void Program_destruct(Program *pr);

#endif
