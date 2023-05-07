#include "operation.h"
#include <string.h>
#include <stdint.h>

void OP_nop(Program *pr) {}

void OP_push32(Program *pr) {
    DS_push(pr->stack, pr->code + pr->ip + 1, 4);
}

void OP_move_sp(Program *pr) {
    pr->stack->top += GETU32();
}

void OP_load_abs32(Program *pr) {
    DS_push(pr->stack, pr->stack->data + GETU32(), 4);
}

void OP_load_rel32(Program *pr) {
    DS_push(pr->stack, pr->stack->data + pr->bp + GETU32(), 4);
}

void OP_store_abs32(Program *pr) {
    uint32_t x = DS_load32(pr->stack, 4);
    memcpy(pr->stack->data + GET32(), &x, 4);
}

void OP_store_rel32(Program *pr) {
    uint32_t x = DS_load32(pr->stack, 4);
    memcpy(pr->stack->data + pr->bp + GET32(), &x, 4);
}

void OP_call(Program *pr) {
    int ret_address = pr->ip + 5;
    DS_push(pr->stack, &ret_address, 4);
    pr->ip = GETU32();
    pr->bp = pr->stack->top;
    // value at bp => previous bp
    DS_push(pr->stack, &pr->bp, 4);
}

// TODO: return values, possibly reserved space on stack which the value is 
// copied to upon return
void OP_ret(Program *pr) {
    pr->ip = *(uint32_t *)(pr->stack->data + pr->bp - 4);
    pr->bp = *(uint32_t *)(pr->stack->data + pr->bp);
}

void OP_jmp(Program *pr) {
    pr->ip = GETU32();
}

void OP_jmp_nz(Program *pr) {
    if (DS_load32(pr->stack, 4)) {
        pr->ip = GETU32();
    }
    pr->stack->top -= 4;
}

void OP_add32(Program *pr) {
    uint32_t result = DS_load32(pr->stack, 4) + DS_load32(pr->stack, 8);
    pr->stack->top -= 8;
    DS_push(pr->stack, &result, 4); 
}

void OP_sub32(Program *pr) {
    uint32_t result = DS_load32(pr->stack, 4) - DS_load32(pr->stack, 8);
    pr->stack->top -= 8;
    DS_push(pr->stack, &result, 4); 
}

void OP_mul32(Program *pr) {
    uint32_t result = DS_load32(pr->stack, 4) * DS_load32(pr->stack, 8);
    pr->stack->top -= 8;
    DS_push(pr->stack, &result, 4); 
}

void OP_div32(Program *pr) {
    uint32_t result = DS_load32(pr->stack, 4) / DS_load32(pr->stack, 8);
    pr->stack->top -= 8;
    DS_push(pr->stack, &result, 4); 
}

void OP_mod32(Program *pr) {
    uint32_t result = DS_load32(pr->stack, 4) % DS_load32(pr->stack, 8);
    pr->stack->top -= 8;
    DS_push(pr->stack, &result, 4); 
}

void OP_and32(Program *pr) {
    uint32_t result = DS_load32(pr->stack, 4) && DS_load32(pr->stack, 8);
    pr->stack->top -= 8;
    DS_push(pr->stack, &result, 4); 
}

void OP_or32(Program *pr) {
    uint32_t result = DS_load32(pr->stack, 4) || DS_load32(pr->stack, 8);
    pr->stack->top -= 8;
    DS_push(pr->stack, &result, 4); 
}
