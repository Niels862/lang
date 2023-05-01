#include "tree.h"
#include <stdlib.h>
#include <stdio.h>

void Tree_print(TreeNode *node, void (*printer)(void *), int indent, int debug) {
    int i;
    if (node == NULL) {
        return;
    }
    for (i = 0; i < indent; i++) {
        printf("  ");
    }
    if (debug) {
        printf("[#[%p] v[%p] >[%p]]: ", node, node->child, node->sibling);
    }
    printf("(#%d) ", node->label);
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
    node->data = node->child = node->sibling = NULL;
    node->label = 0;
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

TreeNode *Tree_make_orphan(TreeNode *parent, TreeNode *child) {
    TreeNode *temp;
    if (parent == NULL || child == NULL) {
        return child;
    }
    if (parent->child == child) {
        parent->child = child->sibling;
    } else {
        temp = parent->child;
        while (temp->sibling != NULL) {
            if (temp->sibling == child) {
                temp->sibling = child->sibling;
                break;
            }
        }
    }
    child->sibling = NULL;
    return child;
}

// Disconnects children from parent, destructs parent and returns children
TreeNode *Tree_make_orphans(TreeNode *parent, void (*destructor)(void *)) {
    TreeNode *child_nodes = parent->child;
    parent->child = NULL;
    Tree_destruct(parent, destructor);
    return child_nodes;
}

TreeNode *Tree_add_child(TreeNode *node, void *data) {
    TreeNode *child = Tree_new_data(data);
    return Tree_add_child_node(node, child);
}

TreeNode *Tree_add_sibling_node(TreeNode *node, TreeNode *sibling) {
    while (node->sibling != NULL) {
        node = node->sibling;
    }
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
