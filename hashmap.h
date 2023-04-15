#ifndef LANG_HASHMAP_H
#define LANG_HASHMAP_H

#define INIT_N_BUCKETS 16
#define LOAD_FACTOR 0.75

typedef struct hashmap_node {
    void *data;
    long long hash;
    struct hashmap_node *next;
} HashMapNode;

typedef struct {
    int entries;
    int threshold;
    int n_buckets;
    HashMapNode **buckets;
    long long (*hash_func)(void *data);
    int (*comp_func)(void *a, void *b);
} HashMap;

long long hash_string(void *str);
int comp_string(void *a, void *b);
void HM_print(HashMap *hashmap);
HashMap *HM_new(
        long long (*hash_func)(void *data),
        int (*comp_func)(void *a, void *b));
int HM_add(HashMap *hashmap, void *data);
int HM_add_string(HashMap *hashmap, char *str);
int HM_remove(HashMap *hashmap, void *data, void (*destructor)(void *));
void HM_rehash(HashMap *hashmap);
void HM_destruct(HashMap *hashmap, void (*destructor)(void *));

#endif //LANG_HASHMAP_H
