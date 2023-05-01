#ifndef STACK_LANG_TREE_H
#define STACK_LANG_TREE_H

typedef struct tree_node {
    void *data;
    int label;
    struct tree_node *child;
    struct tree_node *sibling;
} TreeNode;

void Tree_print(TreeNode *node, void (*printer)(void *), int indent, int debug);
TreeNode *Tree_new();
TreeNode *Tree_new_data(void *data);
TreeNode *Tree_add_child_node(TreeNode *node, TreeNode *child);
TreeNode *Tree_add_child(TreeNode *node, void *data);
TreeNode *Tree_add_sibling_node(TreeNode *node, TreeNode *child);
TreeNode *Tree_make_orphan(TreeNode *parent, TreeNode *child);
TreeNode *Tree_make_orphans(TreeNode *parent, void (*destructor)(void *));
int Tree_count_children(TreeNode *node);
void Tree_destruct(TreeNode *node, void (*destructor)(void *));

#endif
