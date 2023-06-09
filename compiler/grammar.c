#include "grammar.h"
#include <stdlib.h>
#include <stdint.h>

void grammar_node_print(void *data) {
    GrammarNode *gr_node = data;
    printf("[%d:%d] (%d, %d) -> (%d)",
           gr_node->q_low, gr_node->q_high,
           gr_node->ctx, gr_node->token_type, gr_node->target);
}

TreeNode *match(LLNode **pLl_node, TreeNode *rule, TreeNode **rules, int *pMatched) {
    GrammarNode *gr_node = rule->data;
    Token *token = (*pLl_node)->data;
    TreeNode *ast_branch = NULL;
    TreeNode *ast_sibling;
    TreeNode *rule_child;
    LLNode *ll_pos = *pLl_node;
    int matched;
    *pMatched = 1;
    if (gr_node->ctx == CTX_TOKEN) {
        if (gr_node->token_type == token->type
                && (gr_node->target == -1
                    || *(char *)(token->block->data) == gr_node->target)) {
            LL_next(pLl_node);
            return Tree_new_data(Token_copy(token));
        }
    } else if (gr_node->ctx == CTX_ONE_CHILD) {
        rule_child = rule->child;
        while (rule_child != NULL) {
            *pLl_node = ll_pos;
            ast_branch = recursive_descent_parser(pLl_node, rule_child, rules, &matched);
            if (matched) {
                return ast_branch;
            }
            rule_child = rule_child->sibling;
        }
    } else if (gr_node->ctx == CTX_ALL_CHILDREN) {
        rule_child = rule->child;
        while (rule_child != NULL) {
            ast_sibling = recursive_descent_parser(pLl_node, rule_child, rules, &matched);
            if (!matched) {
                break;
            }
            if (ast_sibling != NULL) {
                if (((GrammarNode *)(rule_child->data))->label == -1) {
                    Tree_destruct(ast_sibling, Token_destruct);
                } else if (ast_branch == NULL) {
                    ast_branch = ast_sibling;
                } else {
                    Tree_add_sibling_node(ast_branch, ast_sibling);
                }            
            }
            rule_child = rule_child->sibling;
        }
        if (rule_child == NULL) {
            return ast_branch;
        }
    } else if (gr_node->ctx == CTX_RULE) {
        ast_branch = recursive_descent_parser(
                pLl_node,
                rules[(int)(gr_node->target)],
                rules, &matched);
        if (matched) {
            return ast_branch;
        }
    }
    Tree_destruct(ast_branch, Token_destruct);
    *pLl_node = ll_pos;
    *pMatched = 0;
    return NULL;
}

TreeNode *recursive_descent_parser(LLNode **pLl_node, TreeNode *rule, TreeNode **rules, int *pMatched) {
    TreeNode *ast_node = Tree_new();
    TreeNode *ast_branch;
    GrammarNode *gr_node = rule->data;
    int matched;
    *pMatched = 0;

    if (gr_node->q_low || (!gr_node->q_low && gr_node->q_high)) {
        ast_branch = match(pLl_node, rule, rules, &matched);
        // return if not at least one
        if (ast_branch != NULL) {
            Tree_add_child_node(ast_node, ast_branch);
        } else if (gr_node->q_low && !matched) {
            Tree_destruct(ast_node, Token_destruct);
            return NULL;
        }
    }

    if (!gr_node->q_high) { // q_low or more
        while (1) {
            ast_branch = match(pLl_node, rule, rules, &matched);
            if (!matched) {
                break;
            }
            if (ast_branch != NULL) {
                Tree_add_child_node(ast_node, ast_branch);  
            }
        }
    }
    *pMatched = 1;
    if (gr_node->label == -2) {
        return Tree_make_orphans(ast_node, Token_destruct);
    } else if (gr_node->label != -1) {
        ast_node->label = gr_node->label;
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
    gr_node->label = buffer[*p + 3];
    node->data = gr_node;
    *p += 4;
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
    uint32_t header;
    int i;
    int p = 0;
    fread(&header, 1, 3, file);
    data_size = header & ((1 << 16) - 1);
    *pN_rules = (header >> 16) & ((1 << 8) - 1);
    rules = malloc((*pN_rules) * sizeof(TreeNode));
    buffer = malloc(data_size);
    fread(buffer, 1, data_size, file);
    for (i = 0; i < *pN_rules; i++) {
        rules[i] = parse_grammar_tree(buffer, &p);
    }
    free(buffer);
    return rules;
}
