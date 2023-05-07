#include "datastack.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>

void DS_print(DataStack *stack, int width) {
    print_datablock(stack->data, stack->top, width);
}

DataStack *DS_new() {
    DataStack *stack = malloc(sizeof(DataStack));
    stack->data = malloc(INIT_SIZE);
    stack->top = 0;
    stack->memsize = INIT_SIZE;
    return stack;
}

void DS_expand(DataStack *stack, size_t min_size) {
    int i = 0;
    while (stack->memsize < min_size) {
        stack->memsize *= RESIZE_FACTOR;
        i++;
    }
    if (i) {
        stack->data = realloc(stack->data, stack->memsize);
    }
}

void DS_push(DataStack *stack, void *data, size_t size) {
    if (size <= 0) {
        return;
    }
    if (stack->top + size >= stack->memsize) {
        DS_expand(stack, stack->top + size);
    }
    memcpy(stack->data + stack->top, data, size);
    stack->top += size;
}

void DS_pop(DataStack *stack, void *data, size_t size) {
    memcpy(stack->data - size, data, size);
    stack->top -= size;
}

// relative to stack top
uint32_t DS_load32(DataStack *stack, size_t offset) {
    return *(uint32_t *)(stack->data + stack->top - offset);
}

void DS_destruct(DataStack *stack) {
    free(stack->data);
    free(stack);
}
