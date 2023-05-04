#include "linkedlist.h"
#include <stdlib.h>
#include <stdio.h>

void LL_print(LinkedList *list, void (*printer)(void *)) {
    int i;
    LLNode *node = list->first;
    for (i = 0; i < list->length; i++) {
        if (i) {
            printf(", ");
        }
        printer(node->data);
        node = node->next;
    }
    printf("\n");
}

LinkedList *LL_new() {
    LinkedList *list = malloc(sizeof(LinkedList));
    list->first = list->last = NULL;
    list->length = 0;
    return list;
}

LLNode *LL_add(LinkedList *list, void *data) {
    LLNode *node = malloc(sizeof(LLNode));
    node->data = data;
    node->next = NULL;
    if (list->first == NULL) {
        list->first = node;
        list->last = node;
    } else {
        list->last->next = node;
        list->last = node;
    }
    list->length++;
    return node;
}

LLNode *LL_push(LinkedList *list, void *data) {
    LLNode *node = malloc(sizeof(LLNode));
    node->data = data;
    node->next = list->first;
    if (list->first == NULL) {
        list->first = node;
        list->last = node;
    } else {
        list->first = node;
    }
    list->length++;
    return node;
}

LLNode *LL_pop(LinkedList *list) {
    LLNode *node = list->first;
    if (node == NULL) {
        return NULL;
    }
    list->first = node->next;
    if (node->next == NULL) {
        list->last = NULL;
    }
    node->next = NULL;
    list->length--;
    return node;
}

void LL_next(LLNode **pNode) {
    *pNode = (*pNode)->next;
}

void LL_destruct(LinkedList *list, void (*destructor)(void *)) {
    LLNode *node = list->first;
    LLNode *temp;
    while (node != NULL) {
        temp = node;
        node = node->next;
        if (temp->data != NULL) {
            destructor(temp->data);
        }
        free(temp);
    }
    free(list);
}
