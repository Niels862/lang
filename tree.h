#ifndef STACK_LANG_TREE_H
#define STACK_LANG_TREE_H

typedef struct tree_node {
    void *data;
    struct tree_node *parent;
    struct tree_node *child;
    struct tree_node *sibling;
} TreeNode;

void Tree_print(TreeNode *node, void (*printer)(void *), int indent);
TreeNode *Tree_new();
TreeNode *Tree_add_child(TreeNode *node, void *data);
TreeNode *Tree_add_sibling(TreeNode *node, void *data);
void Tree_destruct(TreeNode *node);

#endif
