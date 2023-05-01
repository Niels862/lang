#ifndef LANG_OPERATOR
#define LANG_OPERATOR

#define N_OPERATORS 2
#define SYMBOL_SIZE 16

typedef struct {
    char string[SYMBOL_SIZE];
    int id;
} Symbol;

enum OperatorID {
    OpAssign, OpLess
};

static Symbol const operators[] = {
    {"=", OpAssign},
    {"<", OpLess}
};

int is_op_char(char c);

#endif
