#include "grammar.h"
#include "lexer.h"
#include <stdlib.h>

void grammar_node_print(void *data) {
    GrammarNode *gr_node = data;
    printf("[%d] [%d]", gr_node->options, gr_node->target);
}

TreeNode *recursive_descent_parser(LLNode **pLl_node, TreeNode *node) {
    GrammarNode *gr_node = node->data;
    Token *token = (*pLl_node)->data;
    int token_type = gr_node >> 4;
    int one = (gr_node >> 2) & 1;
    int more = !((gr_node >> 3) & 1);
    int ctx = gr_node & 3;

    if (one) {

    }
    return NULL;
}

TreeNode *parse_grammar_tree(char *buffer, int *p) {
    int i;
    int n_children = buffer[*p];
    TreeNode *node = Tree_new();
    GrammarNode *gr_node = malloc(sizeof(GrammarNode));
    gr_node->options = buffer[*p + 1];
    gr_node->target = buffer[*p + 2];
    node->data = gr_node;
    *p += 3;
    for (i = 0; i < n_children; i++) {
        Tree_add_child_node(node, parse_grammar_tree(buffer, p));
    }
    return node;
}

// grammar file is assumed to be free of errors
TreeNode **parse_grammar_file(FILE *file) {
    int data_size, n_rules;
    char *buffer;
    TreeNode **rules;
    // first 2 bytes -> size of data section
    // 3rd byte -> amount of rules
    int header;
    int i;
    int p = 0;
    fread(&header, sizeof(char), 3, file);
    data_size = header & ((1 << 16) - 1);
    n_rules = (header >> 16) & ((1 << 8) - 1);
    printf("%d, %d\n", data_size, n_rules);
    rules = malloc(n_rules * sizeof(TreeNode));
    buffer = malloc(data_size * sizeof(char));
    fread(buffer, sizeof(char), data_size, file);
    for (i = 0; i < n_rules; i++) {
        rules[i] = parse_grammar_tree(buffer, &p);
        Tree_print(rules[i], grammar_node_print, 0, 0);
        Tree_destruct(rules[i], free);
    }
    free(buffer);
    return rules;
}
