#include "program.h"

#ifndef LANG_FUNCS
#define LANG_FUNCS

// if addr = -1 then func is used
typedef struct {
    int addr;
    void (*func)(Program *);
} Function;

#endif
