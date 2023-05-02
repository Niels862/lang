#include <stdio.h>
#include "symbol.h"
#include "linkedlist.h"
#include "datablock.h"

#ifndef LANG_LEXER_H
#define LANG_LEXER_H

#define BUFFER_SIZE 256
#define N_KEYWORDS 5

enum TokenType {
    TTKeyword = 0, TTSeparator = 1, TTIdentifier = 2,
    TTIntLit = 3, TTStringLit = 4, TTFloatLit = 5, TTOperator = 6
};

// LTIdentifier -> starting with '_' or alpha
// LTString -> starting with '"'
// LTNumeric -> starting with number
// LTOperator -> starting with op char
enum LexemeType {
    LTEmpty, LTIdentifier, LTString, LTNumeric, LTOperator
};

typedef struct {
    DataBlock *block;
    int line;
    enum TokenType type;
} Token;

void get_token_and_string(void *data, Token **pToken, char **pString);
void Token_print(void *data);
Token *Token_copy(Token *token);
void Token_destruct(void *data);

int is_sep_char(char c);
int lexer_char(char c, LinkedList *tokens, char *lexeme, int *pLexeme_size, int *pLine);
int lexeme_is_symbol(const char *lexeme, int lexeme_size, Symbol const symbols[], int n_symbols, int *n);
int lexeme_is_string(const char *lexeme, int lexeme_size);
int lexeme_is_int(const char *lexeme, int lexeme_size, int *n);
int lexeme_is_float(const char *lexeme, int lexeme_size, double *d);
int lexeme_is_identifier(const char *lexeme, int lexeme_size);
Token *lexeme_to_token(char *lexeme, int lexeme_size, int line);
int lexer(FILE *file, LinkedList *tokens);

#endif
