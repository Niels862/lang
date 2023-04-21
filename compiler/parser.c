#include "parser.h"
#include "grammar.h"
#include "lexer.h"
#include "tree.h"

int parser(LinkedList *tokens) {
    TreeNode **rules;
    TreeNode *ast_root;
    FILE *grammar_file;
    LLNode *ll_node = tokens->first;
    Token *token;
    int n_rules, i;

    grammar_file = fopen("grammar.bin", "rb");
    if (grammar_file == NULL) {
        printf("Parsing error: grammar.bin not found");
        return 1;
    }
    rules = parse_grammar_file(grammar_file, &n_rules);
    ast_root = recursive_descent_parser(&ll_node, rules[0], rules);
    token = ll_node->data;
    printf("AST:\n");
    Tree_print(ast_root, Token_print, 0, 0);
    if (*((char *)token->block->data) == EOF) {
        printf("Successfully parsed input\n");
    } else {
        printf("Parsing error\n");
    }
    Tree_destruct(ast_root, Token_destruct);
    for (i = 0; i < n_rules; i++) {
        Tree_destruct(rules[i], free);
    }
    fclose(grammar_file);
    free(rules);
    return 0;
}
