#ifndef LANG_PROGRAM
#define LANG_PROGRAM

typedef struct {
    unsigned char *stack;
    int ip;
    int sp;
} Program;

#endif
