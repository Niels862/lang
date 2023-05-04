#include <stdlib.h>

#ifndef STACK_LANG_UTILS_H
#define STACK_LANG_UTILS_H

void malloc_string(void **dest, char *source, int length);
void print_datablock(unsigned char *data, size_t size, int width);
void print_num(unsigned int n, int base, int width);
void print_string(char *s, char left, char right);

#endif
