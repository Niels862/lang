#include "program.h"

#ifndef OPERATIONS_H
#define OPERATIONS_H

#define N_OPERATIONS 3

#define GETU32() *(uint32_t *)(pr->code + pr->ip + 1)
#define GET32() *(int32_t *)(pr->code + pr->ip + 1)

typedef struct {
    void (*func)(Program *pr);
    int size; // negative size -> ip should not be incremented
} Operation;

enum OperationID {
    OPNop, OPPush32, OPMoveSP, 
    OPLoadAbs32, OPLoadRel32, OPStoreAbs32, OPStoreRel32,
    OPCall, OPRet, OPJmp, OPJmpNz, 
    OPAdd32, OPSub32, OPMul32, OPDiv32, OPMod32,
    OPAnd32, OPOr32
};

void OP_nop(Program *pr);
void OP_push32(Program *pr);
void OP_move_sp(Program *pr);
void OP_load_abs32(Program *pr);
void OP_load_rel32(Program *pr);
void OP_store_abs32(Program *pr);
void OP_store_rel32(Program *pr);
void OP_call(Program *pr);
void OP_ret(Program *pr);
void OP_jmp(Program *pr);
void OP_jmp_nz(Program *pr);
void OP_add32(Program *pr);
void OP_sub32(Program *pr);
void OP_mul32(Program *pr);
void OP_div32(Program *pr);
void OP_mod32(Program *pr);
void OP_and32(Program *pr);
void OP_or32(Program *pr);

static const Operation operations[] = {
    {OP_nop, 1}, {OP_push32, 5}, {OP_move_sp, 5},
    {OP_load_abs32, 5}, {OP_load_rel32, 5}, 
    {OP_store_abs32, 5}, {OP_store_rel32, 5},
    {OP_call, 5}, {OP_ret, 1}, {OP_jmp, -5}, {OP_jmp_nz, -5},
    {OP_add32, 1}, {OP_sub32, 1}, {OP_mul32, 1}, {OP_div32, 1}, {OP_mod32, 1},
    {OP_and32, 1}, {OP_or32, 1}
};

#endif
