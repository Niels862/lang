#include "datastack.h"
#include <stdio.h>

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

void DS_destruct(DataStack *stack) {
    free(stack->data);
    free(stack);
}
