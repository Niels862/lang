#include <stdio.h>
#include "linkedlist.h"

#ifndef STACK_LANG_LEXER_H
#define STACK_LANG_LEXER_H

#define BUFFER_SIZE 16

 enum TokenType {
    TTKeyword, TTSeparator, TTIdentifier, TTIntLit, TTStringLit, TTFloatLit
};

enum KeywordId {
    KWFunction, KWWhile, KWFor, KWIf, KWElse
};

typedef struct {
    void *data;
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

void print_token(void *data);
void destruct_token(void *data);
int lexer_char(char c, LinkedList *tokens, char *lexeme, int *pLexeme_size, int *pLine);
int lexeme_is_keyword(const char *lexeme, int lexeme_size, int *n);
int lexeme_is_string(const char *lexeme, int lexeme_size);
int lexeme_is_int(const char *lexeme, int lexeme_size, int *n);
int lexeme_is_float(const char *lexeme, int lexeme_size, double *d);
int lexeme_is_identifier(const char *lexeme, int lexeme_size);
Token *lexeme_to_token(char *lexeme, int lexeme_size);
int lexer(FILE *file, LinkedList *tokens);

#endif
