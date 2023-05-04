#include "program.h"

#ifndef OPERATIONS_H
#define OPERATIONS_H

#define N_OPERATIONS 3

typedef void (*Operation)(Program *pr);

enum OperationID {
    OPNop, OPIPush, OPIAdd
};

void OP_nop(Program *pr);
void OP_ipush(Program *pr);
void OP_iadd(Program *pr);

static const Operation operations[] = {
    OP_nop, OP_ipush, OP_iadd
};

#endif
