#include "operation.h"
#include <stdint.h>

void OP_nop(Program *pr) {
    pr->ip++;
}

void OP_ipush(Program *pr) {
    DS_push(pr->stack, pr->code + pr->ip + 1, 4);
    pr->ip += 5;
}

void OP_iadd(Program *pr) {
    int s = DS_load32(pr->stack, 4) + DS_load32(pr->stack, 8);
    pr->stack->top -= 8;
    DS_push(pr->stack, &s, 4); 
    pr->ip += 1;
}
