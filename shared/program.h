#include "datastack.h"
#include <stdio.h>

#ifndef PROGRAM_H
#define PROGRAM_H

typedef struct {
    unsigned char *code;
    DataStack *stack;
    int ip;
    int sp;
    int bp;
} Program;

Program *Program_new();
void Program_open(Program *pr, FILE file);
void Program_destruct(Program *pr);

#endif
