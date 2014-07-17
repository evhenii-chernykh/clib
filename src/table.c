#include "table.h"

#include <assert.h>
#include <stdlib.h>

table_t table_new(table_key_cmp_function_t key_cmp_function, table_key_hash_function_t key_hash_function)
{
    return NULL;
}

void table_free(table_t *table)
{
    assert(table && *table);
}

size_t table_size(table_t table)
{
    assert(table);

    return 0;
}

void *table_add(table_t table, const void *key, const void *value)
{
    assert(table);

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
