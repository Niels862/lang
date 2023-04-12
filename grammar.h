#include <stdio.h>
#include "tree.h"
#include "linkedlist.h"

#ifndef LANG_GRAMMAR_H
#define LANG_GRAMMAR_H

#define CTX_RULE 0
#define CTX_ALL_CHILDREN 1
#define CTX_TOKEN 2
#define CTX_ONE_CHILD 3

typedef struct {
    char q_low;
    char q_high;
    char ctx;
    char token_type;
    char target;
} GrammarNode;

void grammar_node_print(void *data);
int match(TreeNode *ast_node, LLNode **pLl_node, TreeNode *rule, TreeNode **rules);
TreeNode *recursive_descent_parser(LLNode **pLl_node, TreeNode *rule, TreeNode **rules);
TreeNode *parse_grammar_tree(char *buffer, int *p);
TreeNode **parse_grammar_file(FILE *file, int *pN_rules);

#endif
