#include "parser.h"
#include "lexer.h"

int parser(LinkedList *tokens) {
    TreeNode *ast = Tree_new();
    Token *token;
    LLNode *ll_node = tokens->first;

    while (ll_node != NULL) {
        token = ll_node->data;
        Tree_add_child(ast, token);
        ll_node = ll_node->next;
    }

    Tree_print(ast, print_token, 0);

    Tree_destruct(ast);
    return 0;
}
