#include <stdlib.h>

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
void DS_push();
void DS_pop();
void DS_peek();
void DS_store(int i);
void DS_load(int i);
void DS_destruct(DataStack *stack);

#endif
