#include "datastack.h"

DataStack *DS_new() {
    DataStack *stack = malloc(sizeof(DataStack));
    stack->data = malloc(INIT_SIZE);
    stack->top = 0;
    stack->memsize = INIT_SIZE;
    return stack;
}

void DS_destruct(DataStack *stack) {
    free(stack->data);
    free(stack);
}
