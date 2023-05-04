#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void malloc_string(void **pDest, char *source, int length) {
    *pDest = malloc((length + 1));
    memcpy(*pDest, source, length);
    *((char *)*pDest + length) = '\0';
}

void print_datablock(unsigned char *data, size_t size, int width) {
    int x, y;
    unsigned int i;
    if (size == 0) {
        printf("Empty\n");
        return;
    }
    printf("    ");
    for (x = 0; x < width; x++) {
        print_num(x, 10, 3);
        printf(" ");
    }
    printf("\n");
    i = 0;
    for (y = 0;; y++) {
        print_num(y, 10, 3);
        printf(" ");
        for (x = 0; x < width; x++) {
            print_num(data[i], 10, 3);
            printf(" ");
            i++;
            if (i >= size) {
                printf("\n");
                return;
            }
        }
        printf("\n");
    }
}

void print_num(unsigned int n, int base, int width) {
    int i = 0;
    int digit;
    char buffer[65];
    buffer[64] = '\0';
    while (n || width > 0) {
        digit = n % base;
        if (digit < 10) {
            buffer[63 - i] = (char)(digit + '0');
        } else {
            buffer[63 - i] = (char)(digit - 10 + 'A');
        }
        i++;
        n /= base;
        width--;
    }
    printf("%s", buffer + 64 - i);
}

void print_string(char *s, char left, char right) {
    unsigned char c;
    if (left) {
        printf("%c", left);
    }
    while (*s != '\0') {
        c = *s;
        if (c == '"') {
            printf("\\\"");
        } else if (c >= 32 && c <= 127) {
            printf("%c", c);
        } else if (c == '\n') {
            printf("\\n");
        } else if (c == '\r') {
            printf("\\r");
        } else if (c == '\t') {
            printf("\\t");
        } else {
            printf("\\");
            print_num(c, 16, -1);
        }
        s++;
    }
    if (right) {
        printf("%c", right);
    }
}
