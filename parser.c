#include "parser.h"
#include "grammar.h"
#include "lexer.h"
#include "tree.h"

int ast_value(LLNode **node, TreeNode *ast_node) {
    return 0;
}

int ast_statement(LLNode **node, TreeNode *ast_node) {
    Token *token;
    char *string;
    while (1) {
        get_token_and_string((*node)->data, &token, &string);

        if (token->type == TTSeparator && *string == ';') {
            return 0;
        } else if (token->type == TTSeparator && *string == EOF) {
            return 1;
        } else if (token->type == TTIdentifier) {
            Tree_add_child(ast_node, Token_copy(token));
        } else {
            Tree_add_child(ast_node, Token_copy(token));
        }
        LL_next(node);
    }
}

int ast_args(LLNode **node, TreeNode *ast_node) {
    Token *token;
    char *string;
    int i = 0;
    while (1) {
        get_token_and_string((*node)->data, &token, &string);

        if (token->type == TTSeparator) {
            if (*string == ')' && i) {
                return 0;
            } else if (!(*string == '(' && !i)) {
                return 1;
            }
        } else if (token->type == TTIdentifier) {
            Tree_add_child(ast_node, Token_copy(token));
        } else {
            return 1;
        }
        LL_next(node);
        i++;
    }
}

// called when token is token after '{', returns when token == '}' or EOF
// ast_node = empty node, statements are added as children
int ast_block(LLNode **node, TreeNode *ast_node) {
    Token *token;
    char *string;
    while (1) {
        get_token_and_string((*node)->data, &token, &string);

        if (token->type == TTKeyword) {
            if (*string == KWFunction) {
                LL_next(node);
                get_token_and_string((*node)->data, &token, &string);
                if (token->type != TTIdentifier) {
                    return 1;
                }
                LL_next(node);
                if (ast_args(node, Tree_add_child(ast_node, Token_copy(token)))) {
                    return 1;
                }
            }
        } else if (token->type == TTSeparator) {
            if (*string == '{') {
                LL_next(node);
                if (ast_block(node, Tree_add_child(ast_node, NULL))) {
                    return 1;
                }
            } else if (*string == '}' || *string == EOF) {
                return 0;
            }
        } else if (token->type == TTIdentifier) {
            if (ast_statement(node, Tree_add_child(ast_node, NULL))) {
                return 1;
            }
        } else {
            Tree_add_child(ast_node, Token_copy(token));
        }
        LL_next(node);
    }
}

int ast_body(LLNode **node, TreeNode *ast_node) {
    return 0;
}

int parser(LinkedList *tokens) {
    TreeNode **rules;
    TreeNode *ast_root;
    FILE *grammar_file;
    LLNode *first = tokens->first;
    int n_rules, i;

    grammar_file = fopen("test.bin", "rb");
    if (grammar_file == NULL) {
        printf("Parsing error: grammar.bin not found");
        return 1;
    }
    rules = parse_grammar_file(grammar_file, &n_rules);
    ast_root = recursive_descent_parser(&first, rules[0], rules);
    Tree_print(ast_root, Token_print, 0, 1);
    Tree_destruct(ast_root, Token_destruct);
    for (i = 0; i < n_rules; i++) {
        Tree_destruct(rules[i], free);
    }
    fclose(grammar_file);
    free(rules);
    return 0;
}
