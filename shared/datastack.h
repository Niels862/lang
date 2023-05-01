#include <stdlib.h>
#include <stdint.h>

#ifndef DATASTACK_H
#define DATASTACK_H

#define INIT_SIZE 256
#define RESIZE_FACTOR 1.5

typedef struct {
    void *data;
    size_t top;
    size_t memsize;
} DataStack;

DataStack *DS_new();
void DS_destruct(DataStack *stack);

#endif
