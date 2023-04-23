#include "stdlibrary.h"
#include "stdio.h"

void std_print(Program *pr) {
    printf("%s\n", pr->stack + pr->stack[pr->sp - 4]);
}

void std_exit(Program *pr) {

}
