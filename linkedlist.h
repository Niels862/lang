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
LLNode *LL_add(LinkedList *list, void *data);
void LL_next(LLNode **pNode);
void LL_destruct(LinkedList *list, void (*destructor)(void *));

#endif
