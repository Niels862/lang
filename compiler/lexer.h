#include <stdio.h>
#include "linkedlist.h"
#include "datablock.h"

#ifndef STACK_LANG_LEXER_H
#define STACK_LANG_LEXER_H

#define BUFFER_SIZE 16

 enum TokenType {
    TTKeyword = 0, TTSeparator = 1, TTIdentifier = 2,
    TTIntLit = 3, TTStringLit = 4, TTFloatLit = 5
};

enum KeywordId {
    KWFunction = 0, KWWhile = 1, KWFor = 2, KWIf = 3, KWElse = 4
};

typedef struct {
    DataBlock *block;
    int line;
    enum TokenType type;
} Token;

typedef struct {
    char string[16];
    enum KeywordId id;
} Keyword;

static const Keyword keywords[] = {
        {"function", KWFunction},
        {"while", KWWhile},
        {"for", KWFor},
        {"if", KWIf},
        {"else", KWElse}
};

void get_token_and_string(void *data, Token **pToken, char **pString);
void Token_print(void *data);
Token *Token_copy(Token *token);
void Token_destruct(void *data);

int lexer_char(char c, LinkedList *tokens, char *lexeme, int *pLexeme_size, int *pLine);
int lexeme_is_keyword(const char *lexeme, int lexeme_size, int *n);
int lexeme_is_string(const char *lexeme, int lexeme_size);
int lexeme_is_int(const char *lexeme, int lexeme_size, int *n);
int lexeme_is_float(const char *lexeme, int lexeme_size, double *d);
int lexeme_is_identifier(const char *lexeme, int lexeme_size);
Token *lexeme_to_token(char *lexeme, int lexeme_size, int line);
int lexer(FILE *file, LinkedList *tokens);

#endif
