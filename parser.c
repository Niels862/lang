#include "parser.h"
#include "lexer.h"
#include "tree.h"

int ast_value(LLNode **node, TreeNode *ast_node) {
    return 0;
}

int ast_statement(LLNode **node, TreeNode *ast_node) {
    return 0;
}

// called when token is token after '{', returns when token == '}' or EOF
// ast_node = empty node, statements are added as children
int ast_block(LLNode **node, TreeNode *ast_node) {
    Token *token;
    char *string;
    do {
        token = (Token *)((*node)->data);
        string = token->data;

        if (token->type == TTSeparator && *string == '{') {
            *node = (*node)->next;
            ast_block(
                    node,
                    Tree_add_child(ast_node, Tree_new())
            );
        } else {
            Tree_add_child(ast_node, Token_copy(token));
        }
        *node = (*node)->next;
    } while (!(token->type == TTSeparator && (*string == '}' || *string == EOF)));
    return 0;
}

int parser(LinkedList *tokens) {
    TreeNode *ast = Tree_new();
    LLNode *ll_node = tokens->first;

    ast_block(&ll_node, ast);

    Tree_print(ast, Token_print, 0);
    Tree_destruct(ast, Token_destruct);
    return 0;
}
