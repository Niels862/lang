#include "lexer.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void print_token(void *data) {
    Token *token = data;
    if (token->data == NULL) {
        printf("NULL");
    } else if (token->type == TTStringLit) {
        print_string((char *)(token->data), '"', '"');
    } else if (token->type == TTIdentifier || token->type == TTSeparator) {
        print_string((char *)(token->data), '<', '>');
    } else if (token->type == TTKeyword) {
        printf("(%s)", keywords[*((int *)token->data)].string);
    } else if (token->type == TTIntLit) {
        printf("%d", *(int *)token->data);
    } else if (token->type == TTFloatLit) {
        printf("%f", *(double *)token->data);
    } else {
        printf("Type %d?", token->type);
    }
}

Token *copy_token(Token *token) {
    Token *copy = malloc(sizeof(Token));
    copy->type = token->type;
    copy->data = malloc(sizeof(token->data));
    memcpy(copy->data, token->data, sizeof(token->data));
    return copy;
}

void destruct_token(void *data) {
    free(((Token *)data)->data);
    free(data);
}

int lexer_char(char c, LinkedList *tokens, char *lexeme, int *pLexeme_size, int *pLine) {
    if (isalpha(c) || isdigit(c) || c == '"' || c == '\'' || c == '.' || c == '_'
            || (*pLexeme_size > 0 && lexeme[0] == '"')) {
        lexeme[*pLexeme_size] = c;
        (*pLexeme_size)++;
        if (c == '"' && *pLexeme_size > 1) {
            LL_add(tokens, lexeme_to_token(lexeme, *pLexeme_size));
            (*pLexeme_size) = 0;
        } else if (c == '\n' || c == EOF) {
            printf("Unexpected EOL: line %d\n", *pLine);
            return 1;
        }
    } else if (c == ' ' || c == '\t' || c == '\n' || c == '(' || c == ')'
            || c == '{' || c == '}' || c == '[' || c == ']' || c == ';' || c == EOF) {
        if (*pLexeme_size) {
            LL_add(tokens, lexeme_to_token(lexeme, *pLexeme_size));
            (*pLexeme_size) = 0;
        }
        if (c != ' ' && c != '\t') {
            LL_add(tokens, lexeme_to_token(&c, 1));
        }
        if (c == '\n') {
            (*pLine)++;
        }
    }
    return 0;
}

int lexeme_is_keyword(const char *lexeme, int lexeme_size, int *n) {
    int i;
    int n_keywords = sizeof(keywords) / sizeof(Keyword);
    for (i = 0; i < n_keywords; i++) {
        if (memcmp(lexeme, keywords[i].string, lexeme_size) == 0) {
            *n = i;
            return 1;
        }
    }
    return 0;
}

int lexeme_is_string(const char *lexeme, int lexeme_size) {
    return lexeme[0] == '"' && lexeme[lexeme_size - 1] == '"'
        && lexeme_size > 1;
}

int lexeme_is_int(const char *lexeme, int lexeme_size, int *n) {
    int i;
    char c;
    *n = 0;
    for (i = 0; i < lexeme_size; i++) {
        c = lexeme[i];
        if (isdigit(c)) {
            *n *= 10;
            *n += c - '0';
        } else {
            return 0;
        }
    }
    return 1;
}

int lexeme_is_float(const char *lexeme, int lexeme_size, double *d) {
    int i;
    char c;
    int fraction_part_size = 0;
    int past_decimal_sep = 0;
    *d = 0;
    for (i = 0; i < lexeme_size; i++) {
        c = lexeme[i];
        if (isdigit(c)) {
            *d *= 10;
            *d += c - '0';
            if (past_decimal_sep) {
                fraction_part_size++;
            }
        } else if (c == '.' && !past_decimal_sep) {
            past_decimal_sep = 1;
        } else {
            return 0;
        }
    }
    while (fraction_part_size) {
        *d /= 10;
        fraction_part_size--;
    }
    return 1;
}

int lexeme_is_identifier(const char *lexeme, int lexeme_size) {
    int i;
    char c;
    if (lexeme_size > 0 && isdigit(lexeme[0])) {
        return 0;
    }
    for (i = 0; i < lexeme_size; i++) {
        c = lexeme[i];
        if (!(isalpha(c) || isdigit(c) || c == ' ')) {
            return 0;
        }
    }
    return 1;
}

Token *lexeme_to_token(char *lexeme, int lexeme_size) {
    Token *token = malloc(sizeof(Token));
    token->data = NULL;
    int n;
    double d;

    if (lexeme_is_keyword(lexeme, lexeme_size, &n)) {
        token->type = TTKeyword;
        token->data = malloc(sizeof(int));
        *((int *)token->data) = n;
    } else if (lexeme_is_string(lexeme, lexeme_size)) {
        token->type = TTStringLit;
        malloc_string(&token->data, lexeme + 1, lexeme_size - 2);
    } else if (lexeme_is_int(lexeme, lexeme_size, &n)) {
        token->type = TTIntLit;
        token->data = malloc(sizeof(int));
        *((int *)token->data) = n;
    } else if (lexeme_is_float(lexeme, lexeme_size, &d)) {
        token->type = TTFloatLit;
        token->data = malloc(sizeof(double));
        *((double *)token->data) = d;
    } else if (lexeme_is_identifier(lexeme, lexeme_size)) {
        token->type = TTIdentifier;
        malloc_string(&token->data, lexeme, lexeme_size);
    } else if (lexeme_size == 1) {
        token->type = TTSeparator;
        malloc_string(&token->data, lexeme, lexeme_size);
    } else {
        printf("Error while parsing token: %.*s\n", lexeme_size, lexeme);
    }
    return token;
}

int lexer(FILE *file, LinkedList *tokens) {
    char buffer[BUFFER_SIZE];
    char lexeme[256];
    size_t n_read;
    int lexeme_size = 0, line = 1;
    int i;
    do {
        n_read = fread(buffer, sizeof(char), BUFFER_SIZE, file);
        for (i = 0; i < n_read; i++) {
            if (lexer_char(buffer[i], tokens, lexeme, &lexeme_size, &line)) {
                return 1;
            }
        }
    } while (n_read);
    if (lexer_char(EOF, tokens, lexeme, &lexeme_size, &line)) {
        return 1;
    }
    return 0;
}
