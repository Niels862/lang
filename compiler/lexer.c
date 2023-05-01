#include "lexer.h"
#include "datablock.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void get_token_and_string(void *data, Token **pToken, char **pString) {
    *pToken = data;
    if ((*pToken)->block == NULL) {
        *pString = NULL;
    } else {
        *pString = (*pToken)->block->data;
    }
}

void Token_print(void *data) {
    Token *token;
    char *string;
    get_token_and_string(data, &token, &string);
    if (string == NULL) {
        printf("NULL");
    } else if (token->type == TTStringLit) {
        print_string((char *)(token->block->data), '"', '"');
    } else if (token->type == TTIdentifier || token->type == TTSeparator) {
        print_string((char *)(token->block->data), '<', '>');
    } else if (token->type == TTKeyword) {
        printf("(%s)", keywords[*((int *)token->block->data)].string);
    } else if (token->type == TTIntLit) {
        printf("%d", *(int *)token->block->data);
    } else if (token->type == TTFloatLit) {
        printf("%f", *(double *)token->block->data);
    } else if (token->type == TTOperator) {
        printf("{%s}", operators[*((int *)token->block->data)].string);
    } else {
        printf("Type %d?", token->type);
    }
}

Token *Token_copy(Token *token) {
    Token *copy = malloc(sizeof(Token));
    copy->block = DB_new_copy(token->block->data, token->block->size);
    copy->line = token->line;
    copy->type = token->type;
    return copy;
}

void Token_destruct(void *data) {
    DB_destruct(((Token *)data)->block);
    free(data);
}

int is_sep_char(char c) {
    return c == ' ' || c == ';' || c == '{' || c == '}' || c == '(' || c == ')'
            || c == ',' || c == '\n' || c == EOF;
}

int lexer_char(char c, LinkedList *tokens, char *lexeme, int *pLexeme_size, int *pLine) {
    enum LexemeType type;
    if (*pLexeme_size == 0) {
        type = LTEmpty;
    } else if (isalpha(lexeme[0]) || lexeme[0] == '_') {
        type = LTIdentifier;
    } else if (lexeme[0] == '"') {
        type = LTString;
    } else if (isdigit(lexeme[0])) {
        type = LTNumeric;
    } else if (is_op_char(lexeme[0])) {
        type = LTOperator;
    } else {
        type = -1;
    }
    if ( // char extends current lexeme
        (type == LTEmpty && 
            (isalpha(c) || isdigit(c) || is_op_char(c) || c == '_' || c == '"'))
        || (type == LTIdentifier && (isalpha(c) || isdigit(c) || c == '_'))
        || (type == LTNumeric 
            && (isdigit(c) || isalpha(c) || c == '_' || c == '.'))
        || (type == LTString)
    ) {
        lexeme[*pLexeme_size] = c;
        (*pLexeme_size)++;
        if (type == LTString) {
            if (c == '"') {
                LL_add(tokens, lexeme_to_token(lexeme, *pLexeme_size, *pLine));
                (*pLexeme_size) = 0;
            } else if (c == '\n' || c == EOF) {
                printf("Unexpected EOL: line %d\n", *pLine);
                return 1;
            }
        }
    } else { // char terminates current lexeme
        if (*pLexeme_size) {
            LL_add(tokens, lexeme_to_token(lexeme, *pLexeme_size, *pLine));
            (*pLexeme_size) = 0;
        }
        if (is_sep_char(c) && c != ' ' && c != '\n') {
            LL_add(tokens, lexeme_to_token(&c, 1, *pLine));
        }
        if (c == '\n' || c == EOF) {
            (*pLine)++;
        }
    }
    return 0;
}

int lexeme_is_symbol(const char *lexeme, int lexeme_size, Symbol const symbols[], int n_symbols, int *n) {
    int i;
    // symbol size includes null, lexeme size does not 
    // (lexemes not null-terminated)
    if (lexeme_size >= SYMBOL_SIZE) {
        return 0;
    }
    for (i = 0; i < n_symbols; i++) {
        if (memcmp(lexeme, symbols[i].string, lexeme_size) == 0 
                && symbols[i].string[lexeme_size] == '\0') {
            *n = symbols[i].id;
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

Token *lexeme_to_token(char *lexeme, int lexeme_size, int line) {
    Token *token = malloc(sizeof(Token));
    token->line = line;
    int n;
    double d;

    if (lexeme_is_symbol(lexeme, lexeme_size, keywords, N_KEYWORDS, &n)) {
        token->type = TTKeyword;
        token->block = DB_new_copy(&n, sizeof(int));
    } else if (lexeme_is_symbol(lexeme, lexeme_size, operators, N_OPERATORS, &n)) {
        token->type = TTOperator;
        token->block = DB_new_copy(&n, sizeof(int));
    } else if (lexeme_is_string(lexeme, lexeme_size)) {
        token->type = TTStringLit;
        token->block = DB_new_string(lexeme + 1, lexeme_size - 2);
    } else if (lexeme_is_int(lexeme, lexeme_size, &n)) {
        token->type = TTIntLit;
        token->block = DB_new_copy(&n, sizeof(int));
    } else if (lexeme_is_float(lexeme, lexeme_size, &d)) {
        token->type = TTFloatLit;
        token->block = DB_new_copy(&d, sizeof(double));
    } else if (lexeme_is_identifier(lexeme, lexeme_size)) {
        token->type = TTIdentifier;
        token->block = DB_new_string(lexeme, lexeme_size);
    } else if (lexeme_size == 1) {
        token->type = TTSeparator;
        token->block = DB_new_string(lexeme, lexeme_size);
    } else { // TODO: better invalid token error handling
        printf("Error while parsing token: %.*s\n", lexeme_size, lexeme);
    }
    return token;
}

int lexer(FILE *file, LinkedList *tokens) {
    char buffer[BUFFER_SIZE];
    char lexeme[256];
    size_t n_read;
    int lexeme_size = 0;
    int line = 1;
    unsigned int i;
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
