#include "table.h"

#include <assert.h>
#include <stdlib.h>

#define MAX_LOAD 0.75
#define STARTING_BUCKET_COUNT 32

struct pair
{
    const void *key;
    void *value;
    struct pair *next;
};

struct table_type
{
    size_t entryes_count;
    size_t buckets_count;
    table_key_cmp_function_t cmp;
    table_key_hash_function_t hash;
    struct pair **buckets;
};

static int table_enlarge(table_t table)
{
    struct pair **new_buckets, **old_buckets, *p, *v;
    size_t new_buckets_cnt, old_buckets_cnt, i;
    uint32_t hash;

    old_buckets_cnt = table->buckets_count;
    new_buckets_cnt = 2 * old_buckets_cnt;
    new_buckets = malloc(new_buckets_cnt * sizeof(struct pair *));

    if (!new_buckets)
    {
        return 0;
    }

    for (i = 0; i < new_buckets_cnt; i++)
    {
        new_buckets[i] = NULL;
    }

    old_buckets = table->buckets;

    for (i = 0; i < old_buckets_cnt; i++)
    {
        for (p = old_buckets[i]; p; p = p->next)
        {
            v = malloc(sizeof(struct pair));

            if (!v)
            {
                for (i = 0; i < new_buckets_cnt; i++)
                {
                    for (p = new_buckets[i]; p; p = v)
                    {
                        v = p->next;
                        free(p);
                    }
                }

                free(new_buckets);

                return 0;
            }

            hash = table->hash(p->key) % table->buckets_count;
            v->key = p->key;
            v->value = p->value;
            v->next = new_buckets[hash];
            new_buckets[hash] = v;
        }
    }
    
    table->buckets_count = new_buckets_cnt;
    table->buckets = new_buckets;

    for (i = 0; i < old_buckets_cnt; i++)
    {
        for (p = old_buckets[i]; p; p = v)
        {
            v = p->next;
            free(p);
        }
    }

    free(old_buckets);

    return 1;
}

table_t table_new(table_key_cmp_function_t key_cmp_function, table_key_hash_function_t key_hash_function)
{
    table_t table;
    size_t i;

    assert(key_cmp_function && key_hash_function);

    table = malloc(sizeof(struct table_type));

    if (!table)
    {
        return NULL;
    }

    table->buckets = malloc(STARTING_BUCKET_COUNT * sizeof(struct pair *));

    if (!table->buckets)
    {
        free(table);
        return NULL;
    }

    table->entryes_count = 0;
    table->buckets_count = STARTING_BUCKET_COUNT;
    table->cmp = key_cmp_function;
    table->hash = key_hash_function;

    for (i = 0; i < STARTING_BUCKET_COUNT; i++)
    {
        table->buckets[i] = NULL;
    }

    return table;
}

void table_free(table_t *table)
{
    struct pair **buckets, *p, *current;
    size_t i, buckets_cnt;

    assert(table && *table);

    buckets = (*table)->buckets;
    buckets_cnt = (*table)->buckets_count;

    for (i = 0; i < buckets_cnt; i++)
    {
        p = buckets[i];
        while (p)
        {
            current = p;
            p = p->next;
            free(current);
        }
    }

    free(buckets);
    free(*table);
    table = NULL;
}

size_t table_size(table_t table)
{
    assert(table);

    return table->entryes_count;
}

int table_add(table_t table, const void *key, void *value, void **old_value)
{
    struct pair *p, *v, *current;
    uint32_t hash;

    assert(table && key);
    
    if (table->entryes_count > MAX_LOAD * table->buckets_count)
    {
        if (!table_enlarge(table))
        {
            return TABLE_BAD_ALLOC;
        }
    }

    p = malloc(sizeof(struct pair));

    if(!p)
    {
        return TABLE_BAD_ALLOC;
    }

    p->key = key;
    p->value = value;
    hash = table->hash(key) % table->buckets_count;
    v = table->buckets[hash];
    table->buckets[hash] = NULL;

    while (v)
    {
        current = v;
        v = v->next;
        if (table->cmp(key, current->key))
        {
            *old_value = current->value;
            free(current);
        }
        else
        {
            v->next = table->buckets[hash];
            table->buckets[hash] = v;
        }
    }

    p->next = table->buckets[hash];
    table->buckets[hash] = p;
    table->entryes_count++;

    return TABLE_SUCCESS;
}

int table_get(table_t table, const void *key, void **value)
{
    struct pair *p;
    uint32_t hash;

    assert(table);

    hash = table->hash(key) % table->buckets_count;

    for (p = table->buckets[hash]; p; p = p->next)
    {
        if (table->cmp(key, p->key))
        {
            *value = p->value;
            return TABLE_SUCCESS;
        }
    }

    return TABLE_KEY_NOT_EXIST;
}

int table_remove(table_t table, const void *key, void **value)
{
    struct pair *p, *curent;
    uint32_t hash;
    int return_value = TABLE_KEY_NOT_EXIST;

    assert(table);

    hash = table->hash(key) % table->buckets_count;
    p = table->buckets[hash];
    table->buckets[hash] = NULL;
    

    while (p)
    {
        curent = p;
        p = p->next;
        if (table->cmp(key, curent->key))
        {
            *value = curent->value;
            free(curent);
            return_value = TABLE_SUCCESS;
            table->entryes_count--;
        }
        else
        {
            curent->next = table->buckets[hash];
            table->buckets[hash] = curent;
        }
    }

    return return_value;
}

int table_key_exists(table_t table, const void *key)
{
    struct pair *p;
    uint32_t hash;

    assert(table && key);

    hash = table->hash(key) % table->buckets_count;

    for (p = table->buckets[hash]; p; p = p->next)
    {
        if (table->cmp(key, p->key))
        {
            return 1;
        }
    }

    return 0;
}
