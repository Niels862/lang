#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long hash_string(void *data) {
    char *str = data;
    long long hash = 5381;
    char c = *str;
    while (c != '\0') {
        hash = ((hash << 5) + hash) + c;
        str++;
        c = *str;
    }
    return hash;
}

int comp_string(void *data_a, void *data_b) {
    char *a = data_a;
    char *b = data_b;
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
        long long (hash_func)(void *data),
        int (comp_func)(void *a, void *b)) {
    HashMap *hashmap = malloc(sizeof(HashMap));
    hashmap->entries = 0;
    hashmap->threshold = (int)(LOAD_FACTOR * INIT_N_BUCKETS);
    hashmap->n_buckets = INIT_N_BUCKETS;
    hashmap->buckets = calloc(INIT_N_BUCKETS, sizeof(HashMapNode *));
    hashmap->hash_func = hash_func;
    hashmap->comp_func = comp_func;
    return hashmap;
}

int HM_add(HashMap *hashmap, void *data) {
    HashMapNode *temp;
    HashMapNode *node;
    long long hash = hashmap->hash_func(data);
    int bucket = hash & (hashmap->n_buckets - 1);
    node = hashmap->buckets[bucket];
    if (node == NULL) {
        node = malloc(sizeof(HashMapNode));
        hashmap->buckets[bucket] = node;
    } else {
        while (node != NULL) {
            if (node->hash == hash && hashmap->comp_func(node->data, data)) {
                return 1;
            }
            temp = node;
            node = node->next;
        }
        node = malloc(sizeof(HashMapNode));
        temp->next = node;
    }
    node->data = data;
    node->hash = hash;
    node->next = NULL;
    hashmap->entries++;
    if (hashmap->entries > hashmap->threshold) {
        HM_rehash(hashmap);
    }
    return 0;
}

int HM_add_string(HashMap *hashmap, char *str) {
    int len = strlen(str) + 1;
    void *data = malloc(len * sizeof(char));
    memcpy(data, str, len);
    if (HM_add(hashmap, data)) {
        free(data);
        return 1;
    }
    return 0;
}

int HM_remove(HashMap *hashmap, void *data, void (*destructor)(void *)) {
    HashMapNode *temp;
    HashMapNode *prev = NULL;
    long long hash = hashmap->hash_func(data);
    int bucket = hash & (hashmap->n_buckets - 1);
    temp = hashmap->buckets[bucket];
    while (temp != NULL) {
        if (temp->hash == hash && hashmap->comp_func(temp->data, data)) {
            if (prev == NULL) {
                hashmap->buckets[bucket] = temp->next;
            } else {
                prev->next = temp->next;
            }
            destructor(temp->data);
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
    printf("Rehashed:\n");
    HM_print(hashmap);
    printf("B: %d T: %d\n", hashmap->n_buckets, hashmap->threshold);
}

void HM_destruct(HashMap *hashmap, void (*destructor)(void *)) {
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
            destructor(temp->data);
            free(temp);
            temp = next;
        }
    }
    free(hashmap->buckets);
    free(hashmap);
}
