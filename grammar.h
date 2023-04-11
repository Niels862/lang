#include <stdio.h>
#include "tree.h"
#include "linkedlist.h"

#ifndef LANG_GRAMMAR_H
#define LANG_GRAMMAR_H

typedef struct {
    // [4 bits target Token type][]
    char options;
    char target;
} GrammarNode;

void grammar_node_print(void *data);
TreeNode *recursive_descent_parser(LLNode **pLl_node, TreeNode *node);
TreeNode *parse_grammar_tree(char *buffer, int *p);
TreeNode **parse_grammar_file(FILE *file);

#endif
