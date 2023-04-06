#include "lexer.h"
#include "linkedlist.h"
#include "tree.h"

#ifndef STACK_LANG_PARSER_H
#define STACK_LANG_PARSER_H

int ast_value(LLNode *node, TreeNode *ast_node);
int ast_statement(LLNode *node, TreeNode *ast_node);
int ast_block(LLNode *node, TreeNode *ast_node);
int parser(LinkedList *tokens);

#endif