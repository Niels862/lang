#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long hash_string(void *key) {
    char *str = key;
    long long hash = 5381;
    char c = *str;
    while (c != '\0') {
        hash = ((hash << 5) + hash) + c;
        str++;
        c = *str;
    }
    return hash;
}

int comp_string(void *key_a, void *key_b) {
    char *a = key_a;
    char *b = key_b;
    while (*a != '\0' && *b != '\0') {
        if (*a != *b) {
            return 0;
        }
        a++;
        b++;
    }
    return 1;
}

void HM_print(HashMap *hashmap) {
    int i, j;
    HashMapNode *node;
    for (i = 0; i < hashmap->n_buckets; i++) {
        node = hashmap->buckets[i];
        j = 0;
        if (node == NULL) {
            printf("*");
        }
        while (node != NULL) {
            if (j) {
                printf("->");
            }
            printf("%lld", node->hash);
            j++;
            node = node->next;
        }
        printf("\n");
    }
}

HashMap *HM_new(
        long long (hash_func)(void *key),
        int (comp_func)(void *a, void *b),
        void (*key_destructor)(void *),
        void (*value_destructor)(void *)) {
    HashMap *hashmap = malloc(sizeof(HashMap));
    hashmap->entries = 0;
    hashmap->threshold = (int)(LOAD_FACTOR * INIT_N_BUCKETS);
    hashmap->n_buckets = INIT_N_BUCKETS;
    hashmap->buckets = calloc(INIT_N_BUCKETS, sizeof(HashMapNode *));
    hashmap->hash_func = hash_func;
    hashmap->comp_func = comp_func;
    hashmap->key_destructor = key_destructor;
    hashmap->value_destructor = value_destructor;
    return hashmap;
}

void *HM_get(HashMap *hashmap, void *key) {
    HashMapNode *temp;
    long long hash = hashmap->hash_func(key);
    int bucket = hash & (hashmap->n_buckets - 1);
    temp = hashmap->buckets[bucket];
    while (temp != NULL) {
        if (temp->hash == hash && hashmap->comp_func(temp->key, key)) {
            return temp->value;
        }
        temp = temp->next;
    }
    return NULL;
}

int HM_add(HashMap *hashmap, void *key, void *value) {
    HashMapNode *temp;
    HashMapNode *node;
    long long hash = hashmap->hash_func(key);
    int bucket = hash & (hashmap->n_buckets - 1);
    temp = hashmap->buckets[bucket];
    while (temp != NULL) {
        if (temp->hash == hash && hashmap->comp_func(temp->key, key)) {
            return 1;
        }
        temp = temp->next;
    }
    node = malloc(sizeof(HashMapNode));
    node->next = hashmap->buckets[bucket];
    hashmap->buckets[bucket] = node;
    node->key = key;
    node->value = value;
    node->hash = hash;
    hashmap->entries++;
    if (hashmap->entries > hashmap->threshold) {
        HM_rehash(hashmap);
    }
    return 0;
}

int HM_add_string(HashMap *hashmap, char *str, void *value) {
    int len = strlen(str) + 1;
    void *key = malloc(len * sizeof(char));
    memcpy(key, str, len);
    if (HM_add(hashmap, key, value)) {
        free(key);
        return 1;
    }
    return 0;
}

int HM_remove(HashMap *hashmap, void *key) {
    HashMapNode *temp;
    HashMapNode *prev = NULL;
    long long hash = hashmap->hash_func(key);
    int bucket = hash & (hashmap->n_buckets - 1);
    temp = hashmap->buckets[bucket];
    while (temp != NULL) {
        if (temp->hash == hash && hashmap->comp_func(temp->key, key)) {
            if (prev == NULL) {
                hashmap->buckets[bucket] = temp->next;
            } else {
                prev->next = temp->next;
            }
            hashmap->key_destructor(temp->key);
            if (temp->value != NULL) {
                hashmap->value_destructor(temp->value);
            }
            free(temp);
            return 0;
        }
        prev = temp;
        temp = temp->next;
    }
    return 1;
}

void HM_rehash(HashMap *hashmap) {
    HashMapNode **new_buckets;
    HashMapNode *temp;
    HashMapNode *next;
    int i, bucket;
    new_buckets = calloc(2 * hashmap->n_buckets, sizeof(HashMapNode *));

    for (i = 0; i < hashmap->n_buckets; i++) {
        temp = hashmap->buckets[i];
        while (temp != NULL) {
            next = temp->next;
            bucket = temp->hash & (hashmap->n_buckets - 1);
            temp->next = new_buckets[bucket];
            new_buckets[bucket] = temp;
            temp = next;
        }
    }
    free(hashmap->buckets);
    hashmap->buckets = new_buckets;
    hashmap->n_buckets *= 2;
    hashmap->threshold = (int)(LOAD_FACTOR * hashmap->n_buckets);
}

void HM_destruct(HashMap *hashmap) {
    HashMapNode *temp;
    HashMapNode *next;
    int i;
    if (hashmap == NULL) {
        return;
    }
    for (i = 0; i < hashmap->n_buckets; i++) {
        temp = hashmap->buckets[i];
        while (temp != NULL) {
            next = temp->next;
            hashmap->key_destructor(temp->key);
            if (temp->value != NULL) {
                hashmap->value_destructor(temp->value);
            }
            free(temp);
            temp = next;
        }
    }
    free(hashmap->buckets);
    free(hashmap);
}
