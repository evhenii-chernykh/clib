#include "hash_set.h"

#include <assert.h>
#include <stdlib.h>

#define MAX_LOAD 0.75
#define STARTING_BUCKET_COUNT 32

struct hash_set_entry
{
    const void *key;
    struct hash_set_entry *next;
};

struct hash_set_type
{
    size_t entryes_count;
    size_t buckets_count;
    hash_set_cmp_function_t cmp;
    hash_set_hash_function_t hash;
    struct hash_set_entry **buckets;
};

hash_set_t hash_set_new(hash_set_cmp_function_t cmp, hash_set_hash_function_t hash)
{
    hash_set_t hash_set;
    size_t i;

    assert(cmp && hash);

    hash_set = malloc(sizeof(struct hash_set_type));
    
    if (!hash_set)
    {
        return NULL;
    }

    hash_set->buckets = malloc(STARTING_BUCKET_COUNT * sizeof(struct hash_set_entry*));

    if (!hash_set->buckets)
    {
        free(hash_set);
        return NULL;
    }

    for (i = 0; i < STARTING_BUCKET_COUNT; i++)
    {
        hash_set->buckets[i] = NULL;
    }

    hash_set->entryes_count = 0;
    hash_set->buckets_count = STARTING_BUCKET_COUNT;
    hash_set->cmp = cmp;
    hash_set->hash = hash;

    return hash_set;
}

void hash_set_free(hash_set_t *hash_set)
{
    struct hash_set_entry *p, *current;
    size_t i;

    assert(hash_set && *hash_set);

    for (i = 0; i < (*hash_set)->buckets_count; i++)
    {
        p = (*hash_set)->buckets[i];
        while (p)
        {
            current = p;
            p = p->next;
            free(current);
        }
    }

    free(*hash_set);
    *hash_set = NULL;
}

size_t hash_set_size(hash_set_t hash_set)
{
    assert(hash_set);

    return hash_set->entryes_count;
}

int hash_set_add(hash_set_t hash_set, const void *element)
{
    struct hash_set_entry *p;
    uint32_t hash;

    assert(hash_set && element);

    hash = hash_set->hash(element) % hash_set->buckets_count;

    for (p = hash_set->buckets[hash]; p; p = p->next)
    {
        if (hash_set->cmp(element, p->key))
        {
            return HASH_SET_ELEMENT_EXIST;
        }
    }

    p = malloc(sizeof(struct hash_set_entry));

    if (!p)
    {
        return HASH_SET_BAD_ALLOC;
    }

    p->key = element;
    p->next = hash_set->buckets[hash];
    hash_set->buckets[hash] = p;
    hash_set->entryes_count++;

    return HASH_SET_SUCCESS;
}

const void *hash_set_remove(hash_set_t hash_set, const void *element)
{
    struct hash_set_entry *p, *current;
    const void *old_key;
    uint32_t hash;

    assert(hash_set && element);

    old_key = NULL;
    hash = hash_set->hash(element) % hash_set->buckets_count;
    p = hash_set->buckets[hash];
    hash_set->buckets[hash] = NULL;

    while (p)
    {
        current = p;
        p = p->next;

        if (hash_set->cmp(current->key, element))
        {
            old_key = current->key;
            free(current);
            hash_set->entryes_count--;
        }
        else
        {
            current->next = hash_set->buckets[hash];
            hash_set->buckets[hash] = current;
        }
    }

    return old_key;
}

int hash_set_exist(hash_set_t hash_set, const void *element)
{
    struct hash_set_entry *p;
    uint32_t hash;

    assert(hash_set && element);

    hash = hash_set->hash(element) % hash_set->buckets_count;

    for (p = hash_set->buckets[hash]; p; p = p->next)
    {
        if (hash_set->cmp(p->key, element))
        {
            return 1;
        }
    }

    return 0;
}
