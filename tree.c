#include "tree.h"
#include <stdlib.h>
#include <stdio.h>

void Tree_print(TreeNode *node, void (*printer)(void *), int indent, int debug) {
    int i;
    if (node == NULL) {
        return;
    }
    for (i = 0; i < indent; i++) {
        printf("    ");
    }
    if (debug) {
        printf("[#[%p] ^[%p] v[%p] >[%p]]: ", node, node->parent, node->child, node->sibling);
    }
    if (node->data == NULL) {
        printf("*");
    } else {
        printer(node->data);
    }
    printf("\n");
    Tree_print(node->child, printer, indent + 1, debug);
    Tree_print(node->sibling, printer, indent, debug);
}

TreeNode *Tree_new() {
    TreeNode *node = malloc(sizeof(TreeNode));
    node->data = node->child = node->parent = node->sibling = NULL;
    node->child = node->sibling = NULL;
    return node;
}

TreeNode *Tree_new_data(void *data) {
    TreeNode *node = Tree_new();
    node->data = data;
    return node;
}

TreeNode *Tree_add_child_node(TreeNode *node, TreeNode *child) {
    TreeNode *temp;
    child->parent = node;
    if (node->child == NULL) {
        node->child = child;
    } else {
        temp = node->child;
        while (temp->sibling != NULL) {
            temp = temp->sibling;
        }
        temp->sibling = child;
    }
    return child;
}

TreeNode *Tree_add_child(TreeNode *node, void *data) {
    TreeNode *child = malloc(sizeof(TreeNode));
    child->data = data;
    child->sibling = NULL;
    child->child = NULL;
    return Tree_add_child_node(node, child);
}

TreeNode *Tree_add_sibling(TreeNode *node, void *data) {
    TreeNode *sibling = malloc(sizeof(TreeNode));
    sibling->data = data;
    sibling->parent = node->parent;
    sibling->sibling = sibling->child = NULL;
    node->sibling = sibling;
    return sibling;
}

int Tree_count_children(TreeNode *node) {
    TreeNode *child = node->child;
    int n = 0;

    while (child != NULL) {
        child = child->sibling;
        n++;
    }
    return n;
}

void Tree_destruct(TreeNode *node, void (*destructor)(void *)) {
    if (node == NULL) {
        return;
    }
    Tree_destruct(node->sibling, destructor);
    Tree_destruct(node->child, destructor);
    if (node->data != NULL) {
        destructor(node->data);
    }
    free(node);
}
