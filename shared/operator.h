#ifndef LANG_OPERATOR
#define LANG_OPERATOR

enum OperatorID {
    OpAssign
};

typedef struct {
    int id;
    int arity;
    char op[4];
} Operator;

// Operator operators[] = {
//     {OpAssign, 2, "="}
// };

int is_op_char(char c);

#endif
