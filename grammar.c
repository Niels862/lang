#include "grammar.h"
#include "lexer.h"
#include <stdlib.h>

int depth = 0;

void grammar_node_print(void *data) {
    GrammarNode *gr_node = data;
    printf("[%d:%d] (%d, %d) -> (%d)",
           gr_node->q_low, gr_node->q_high,
           gr_node->ctx, gr_node->token_type, gr_node->target);
}

// if rule is a match, adds parsed content to ast_node
int match(TreeNode *ast_node, LLNode **pLl_node, TreeNode *rule, TreeNode **rules) {
    GrammarNode *gr_node = rule->data;
    Token *token = (*pLl_node)->data;
    TreeNode *ast_branch;
    TreeNode *rule_child;
    LLNode *ll_pos = *pLl_node;

    if (gr_node->ctx == CTX_TOKEN) {
        printf("%d %d\n", gr_node->token_type, token->type);
        if (gr_node->token_type == token->type
                && (gr_node->target == -1
                    || *(char *)(token->block->data) == gr_node->target)) {
            Tree_add_child(ast_node, Token_copy(token));
            LL_next(pLl_node);
            return 0;
        }
    } else if (gr_node->ctx == CTX_ONE_CHILD) {
        rule_child = rule->child;
        while (1) {
            ast_branch = recursive_descent_parser(pLl_node, rule_child, rules);
            if (rule_child != NULL) {
                Tree_add_child_node(ast_node, ast_branch);
                LL_next(pLl_node);
                return 0;
            }
            rule_child = rule_child->sibling;
        }
    } else if (gr_node->ctx == CTX_ALL_CHILDREN) {

    }
    *pLl_node = ll_pos;
    return 1;
}

TreeNode *recursive_descent_parser(LLNode **pLl_node, TreeNode *rule, TreeNode **rules) {
    TreeNode *ast_node = Tree_new();
    GrammarNode *gr_node = rule->data;
    int errorcode;

    if (gr_node->q_low || (!gr_node->q_low && gr_node->q_high)) {
        // return if not at least one
        if (match(ast_node, pLl_node, rule, rules) && gr_node->q_low) {
            Tree_destruct(ast_node, Token_destruct);
            return NULL;
        }
    }

    if (!gr_node->q_high) { // q_low or more
        errorcode = 0;
        while (!errorcode) {
            errorcode = match(ast_node, pLl_node, rule, rules);
        }
    }
    return ast_node;
}

TreeNode *parse_grammar_tree(char *buffer, int *p) {
    int i, options;
    int n_children = buffer[*p];
    TreeNode *node = Tree_new();
    GrammarNode *gr_node = malloc(sizeof(GrammarNode));
    options = buffer[*p + 1];
    gr_node->q_low = (options >> 2) & 1;
    gr_node->q_high = (options >> 3) & 1;
    gr_node->ctx = options & 3;
    gr_node->token_type = options >> 4;
    gr_node->target = buffer[*p + 2];
    node->data = gr_node;
    *p += 3;
    for (i = 0; i < n_children; i++) {
        Tree_add_child_node(node, parse_grammar_tree(buffer, p));
    }
    return node;
}

// grammar file is assumed to be free of errors
TreeNode **parse_grammar_file(FILE *file, int *pN_rules) {
    int data_size;
    char *buffer;
    TreeNode **rules;
    // first 2 bytes -> size of data section
    // 3rd byte -> amount of rules
    int header;
    int i;
    int p = 0;
    fread(&header, sizeof(char), 3, file);
    data_size = header & ((1 << 16) - 1);
    *pN_rules = (header >> 16) & ((1 << 8) - 1);
    printf("%d, %d\n", data_size, *pN_rules);
    rules = malloc((*pN_rules) * sizeof(TreeNode));
    buffer = malloc(data_size * sizeof(char));
    fread(buffer, sizeof(char), data_size, file);
    for (i = 0; i < *pN_rules; i++) {
        rules[i] = parse_grammar_tree(buffer, &p);
        Tree_print(rules[i], grammar_node_print, 0, 0);
    }
    free(buffer);
    return rules;
}
