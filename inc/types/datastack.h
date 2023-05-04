#include <stdlib.h>
#include <stdint.h>

#ifndef DATASTACK_H
#define DATASTACK_H

#define INIT_SIZE 256
#define RESIZE_FACTOR 1.5

typedef struct {
    unsigned char *data;
    size_t top;
    size_t memsize;
} DataStack;

void DS_print(DataStack *stack, int width);
DataStack *DS_new();
void DS_expand(DataStack *stack, size_t min_size);
void DS_push(DataStack *stack, void *data, size_t size);
uint32_t DS_load32(DataStack *stack, size_t offset);
void DS_destruct(DataStack *stack);

#endif
