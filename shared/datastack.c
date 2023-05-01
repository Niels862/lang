#include "datastack.h"

DataStack *DS_new() {
    DataStack *stack = malloc(sizeof(DataStack));
    stack->data = malloc(INIT_SIZE);
    stack->top = 0;
    stack->memsize = INIT_SIZE;
}

void DS_push() {
    
}

void DS_pop() {

}

void DS_peek() {

}

void DS_store(int i) {

}

void DS_load(int i) {

}

void DS_destruct(DataStack *stack) {
    free(stack->data);
    free(stack);
}
