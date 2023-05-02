#include "program.h"

#ifndef OPERATIONS_H
#define OPERATIONS_H

#define N_OPERATIONS 0

enum OperationID {
    OPNop,
};

typedef struct {
    void (*func)(Program *pr);
    enum OperationID id;
} Operation;

void OP_nop(Program *pr);

static Operation const operations[] = {
    {OPNop, OPNop}
};

#endif
