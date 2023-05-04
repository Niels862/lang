#include "program.h"

#ifndef OPERATIONS_H
#define OPERATIONS_H

#define N_OPERATIONS 3

enum OperationID {
    OPNop, OPIPush, OPIAdd
};

typedef struct {
    void (*func)(Program *pr);
    enum OperationID id;
} Operation;

void OP_nop(Program *pr);
void OP_ipush(Program *pr);
void OP_iadd(Program *pr);

static Operation const operations[] = {
    {OP_nop, OPNop},
    {OP_ipush, OPIPush},
    {OP_iadd, OPIAdd}
};

#endif
