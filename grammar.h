#include <stdio.h>
#include "tree.h"
#include "linkedlist.h"

#ifndef LANG_GRAMMAR_H
#define LANG_GRAMMAR_H

typedef struct {
    char options;
    char target;
} GrammarNode;

TreeNode **parse_grammar_file(FILE *file);

#endif
