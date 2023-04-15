#ifndef LANG_HASHMAP_H
#define LANG_HASHMAP_H

#define INIT_N_BUCKETS 16
#define LOAD_FACTOR 0.75

typedef struct hashmap_node {
    void *key;
    void *value;
    long long hash;
    struct hashmap_node *next;
} HashMapNode;

typedef struct {
    int entries;
    int threshold;
    int n_buckets;
    HashMapNode **buckets;
    long long (*hash_func)(void *key);
    int (*comp_func)(void *a, void *b);
    void (*key_destructor)(void *);
    void (*value_destructor)(void *);
} HashMap;

long long hash_string(void *str);
int comp_string(void *a, void *b);
void HM_print(HashMap *hashmap);
HashMap *HM_new(
        long long (*hash_func)(void *key),
        int (*comp_func)(void *a, void *b),
        void (*key_destructor)(void *),
        void (*value_destructor)(void *));
int HM_add(HashMap *hashmap, void *key, void *value);
void *HM_get(HashMap *hashmap, void *key);
int HM_add_string(HashMap *hashmap, char *key, void *value);
int HM_remove(HashMap *hashmap, void *key);
void HM_rehash(HashMap *hashmap);
void HM_destruct(HashMap *hashmap);

#endif //LANG_HASHMAP_H
