#include "table.h"

#include <assert.h>
#include <stdlib.h>

#define MAX_LOAD 0.75
#define STARTING_BUCKET_COUNT 32

struct pair
{
    const void *key;
    const void *value;
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

static void table_enlarge(table_t table)
{
    struct pair **new_buckets, **old_buckets, *p, *v;
    size_t new_buckets_cnt, old_buckets_cnt, i;
    uint32_t hash;

    old_buckets_cnt = table->buckets_count;
    new_buckets_cnt = 2 * old_buckets_cnt;
    new_buckets = malloc(new_buckets_cnt * sizeof(struct pair *));

    if (!new_buckets)
    {
        return;
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

                return;
            }

            hash = table->hash(p->key);
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
    struct pair **buckets, *p, *v;
    size_t i, buckets_cnt;

    assert(table && *table);

    buckets = (*table)->buckets;
    buckets_cnt = (*table)->buckets_count;

    for (i = 0; i < buckets_cnt; i++)
    {
        for (p = buckets[i]; p; p = v)
        {
            v = p->next;
            free(p);
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

void *table_add(table_t table, const void *key, const void *value)
{
    struct pair *p;

    assert(table && key);

    p = malloc(sizeof(struct pair));

    if(!p)
    {
        return NULL;
    }

    return NULL;
}

void *table_get(table_t table, const void *key)
{
    assert(table);

    return NULL;
}

void *table_remove(table_t table, const void *key)
{
    assert(table);

    return NULL;
}

int table_key_exists(table_t table, const void *key)
{
    assert(table);

    return 0;
}
