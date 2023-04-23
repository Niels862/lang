#ifndef LANG_OPERATOR
#define LANG_OPERATOR

#define N_OPERATORS 2

typedef struct {
    char string[16];
    int id;
} Symbol;

enum OperatorID {
    OpAssign
};

static Symbol const operators[] = {
    {"=", OpAssign}
};

int is_op_char(char c);

#endif
