#ifndef LANG_OPERATOR
#define LANG_OPERATOR

#define N_OPERATORS 2
#define SYMBOL_SIZE 16

enum SymbolID {
    SymEqual, SymLess
};

enum KeywordId {
    KWFunction = 0, KWWhile = 1, KWFor = 2, KWIf = 3, KWElse = 4
};

typedef struct {
    char string[SYMBOL_SIZE];
    int id;
} Symbol;

static Symbol const operators[] = {
    {"=", SymEqual},
    {"<", SymLess}
};

static Symbol const keywords[] = {
    {"function", KWFunction},
    {"while", KWWhile},
    {"for", KWFor},
    {"if", KWIf},
    {"else", KWElse}
};

int is_op_char(char c);

#endif
