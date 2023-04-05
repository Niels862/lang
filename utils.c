#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void malloc_string(void **pDest, char *source, int length) {
    *pDest = malloc((length + 1) * sizeof(char));
    memcpy(*pDest, source, length * sizeof(char));
    *((char *)*pDest + length) = '\0';
}

void print_num(int n, int base) {
    int i = 0;
    int digit;
    char buffer[20];
    while (n) {
        digit = n % base;
        if (digit < 10) {
            buffer[i] = (char)(digit + '0');
        } else {
            buffer[i] = (char)(digit - 10 + 'A');
        }
        i++;
        n /= base;
    }
    buffer[i] = '\0';
    printf("%s", buffer);
}

void print_string(char *s, char left, char right) {
    if (left) {
        printf("%c", left);
    }
    while (*s != '\0') {
        if (*s == '"') {
            printf("\\\"");
        } else if (*s >= 32 && *s <= 127) {
            printf("%c", *s);
        } else if (*s == '\n') {
            printf("\\n");
        } else if (*s == '\r') {
            printf("\\r");
        } else if (*s == '\t') {
            printf("\\t");
        } else {
            printf("\\");
            print_num(*s, 16);
        }
        s++;
    }
    if (right) {
        printf("%c", right);
    }
}
