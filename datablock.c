#include "datablock.h"
#include <string.h>

DataBlock *DB_new(void *data, size_t size) {
    DataBlock *block = malloc(sizeof(DataBlock));
    block->data = data;
    block->size = size;
    return block;
}

DataBlock *DB_new_copy(void *data, size_t size) {
    void *copied_data = malloc(size);
    memcpy(copied_data, data, size);
    return DB_new(copied_data, size);
}

// makes new block of size strlength + 1 and sets the last byte to '\0'
DataBlock *DB_new_string(void *data, size_t strlength) {
    void *copied_data = malloc(strlength + 1);
    memcpy(copied_data, data, strlength);
    *((char *)copied_data + strlength) = '\0';
    return DB_new(copied_data, strlength + 1);
}

void DB_destruct(void *block) {
    free(((DataBlock *)block)->data);
    free(block);
}
