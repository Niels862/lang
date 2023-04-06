#include <stdlib.h>

#ifndef LANG_DATABLOCK_H
#define LANG_DATABLOCK_H

typedef struct {
    void *data;
    size_t size;
} DataBlock;

DataBlock *DB_new(void *data, size_t size);
DataBlock *DB_new_copy(void *data, size_t size);
DataBlock *DB_new_string(void *data, size_t strlength);
void DB_destruct(void *block);

#endif //LANG_DATABLOCK_H
