#ifndef STACK_LANG_LINKEDLIST_H
#define STACK_LANG_LINKEDLIST_H

typedef struct linked_list_node {
    void *data;
    struct linked_list_node *next;
} LLNode;

typedef struct {
    LLNode *first;
    LLNode *last;
    int length;
} LinkedList;

void LL_print(LinkedList *list, void (*printer)(void *));
LinkedList *LL_new();
// Adds to end of list and returns node
LLNode *LL_add(LinkedList *list, void *data);
// Adds to start of list and returns node
LLNode *LL_push(LinkedList *list, void *data);
// Pops from start of list if non-empty, else NULL
LLNode *LL_pop(LinkedList *list);
void LL_next(LLNode **pNode);
void LL_destruct(LinkedList *list, void (*destructor)(void *));

#endif
