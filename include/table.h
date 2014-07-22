#ifndef TABLE_H_INCLUDED__
#define TABLE_H_INCLUDED__

#include <stddef.h>
#include <stdint.h>

#define TABLE_KEY_NOT_EXIST 0
#define TABLE_BAD_ALLOC     1
#define TABLE_SUCCESS       2


struct table_type;
typedef struct table_type *table_t;

/* Function type for comparsion keys if keys equal it should return non zero value and zero in other case. */
typedef int (*table_key_cmp_function_t)(const void *key1, const void *key2);

/* Function typr for hashing keys. */
typedef uint32_t (*table_key_hash_function_t)(const void *key);

/*
 * Creates table, if it is not enough memory it returns NULL.
 */
extern table_t table_new(table_key_cmp_function_t key_cmp_function, table_key_hash_function_t key_hash_function);

/*
 * Dealocates table memory.
 */
extern void table_free(table_t *table);

/*
 * Returns number of key->value pairs in table.
 */
extern size_t table_size(table_t table);

/*
 * Adds key value pair to the table, if key exist *old_value will containt previous value
 * of this key. Return TABLE_BAD_ALLOC, if it can not allocate memory for entry, and 
 * TABLE_SUCCESS if key value pair was added.
 */
extern int table_add(table_t table, const void *key, void *value, void **old_value);

/*
 * Gets value from table by it key. Value vil be stored in *value.
 * If key does not exist it returns TABLE_KEY_NOT_EXIST, and TABLE_SUCCESS
 * if key exists and was found.
 */ 
extern int table_get(table_t table, const void *key, void **value);

/*
 * Removes key value pair from table. Value vil be stored at *value.
 * If key does not exist it returns TABLE_KEY_NOT_EXIST, and TABLE_SUCCESS
 * if key exists and was removed.
 */
extern int table_remove(table_t table, const void *key, void **value);

/*
 * Check existance of the key in table, if it exists returns non zero value and
 * zero value in other case.
 */
extern int table_key_exists(table_t table, const void *key);

#endif /* TABLE_H_INCLUDED__ */
