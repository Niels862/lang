#include "func.h"
#include "program.h"

#ifndef LANG_STDLIBRARY
#define LANG_STDLIBRARY

void std_print(Program *pr);
void std_exit(Program *pr);

static const Function stdlib_functions[] = {
    {-1, std_print},
    {-1, std_exit}
};

#endif
