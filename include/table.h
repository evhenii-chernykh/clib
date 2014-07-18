#ifndef TABLE_H_INCLUDED__
#define TABLE_H_INCLUDED__

#include <stddef.h>
#include <stdint.h>

struct table_type;
typedef struct table_type *table_t;

typedef int (*table_key_cmp_function_t)(const void *key1, const void *key2);

typedef uint32_t (*table_key_hash_function_t)(const void *key);

extern table_t table_new(table_key_cmp_function_t key_cmp_function, table_key_hash_function_t key_hash_function);

extern void table_free(table_t *table);

extern size_t table_size(table_t table);

extern void *table_add(table_t table, const void *key, const void *value);

extern void *table_get(table_t table, const void *key);

extern void *table_remove(table_t table, const void *key);

extern int table_key_exists(table_t table, const void *key);

#endif /* TABLE_H_INCLUDED__ */
