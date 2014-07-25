#ifndef HASH_SET_H_INCLUDED__
#define HASH_SET_H_INCLUDED__

#include <stdint.h>
#include <stddef.h>

#define HASH_SET_BAD_ALLOC     0
#define HASH_SET_ELEMENT_EXIST 1
#define HASH_SET_SUCCESS       2

struct hash_set_type;
typedef struct hash_set_type *hash_set_t;

/**
 * Function type for comparsing elememts in the hash set.
 * Should return non zero value if elements is equal and zero if not.
 */
typedef int (*hash_set_cmp_function_t)(const void *element1, const void *element2);

/**
 * Function type for hashing elements in hash set.
 */
typedef uint32_t (*hash_set_hash_function_t)(const void *element);

/**
 * Creates new hash set, return NULL pointer if it is not enough memory.
 */
extern hash_set_t hash_set_new(hash_set_cmp_function_t cmp, hash_set_hash_function_t hash);

/**
 * Frees memory used by hash set and set its pointer to NULL;
 */
extern void hash_set_free(hash_set_t *hash_set);

/**
 * Return number of elements in the hash set.
 */
extern size_t hash_set_size(hash_set_t hash_set);

/**
 * Add new element to hash set, if it exists (cmp function return 1) element would not be added.
 * Element could not be NULL pointer it will be cause assertion.
 * Return HASH_SET_BAD_ALLOC if failed to allocate memory for new entry,
 *        HASH_SET_ELEMENT_EXIST if element alredy exists,
 *        HASH_SET_SUCCESS if element successfuly added.
 */
extern int hash_set_add(hash_set_t hash_set, const void *element);

/**
 * Remove element from hash set and return pointer to it, return NULL if such element does not exist.
 * Element could not be NULL pointer it will be cause assertion.
 */
extern const void *hash_set_remove(hash_set_t hash_set, const void *element);

/**
 * Check existance of element in hash set, if it exists return non zero value and zero if not.
 * Element could not be NULL pointer it will be cause assertion.
 */
extern int hash_set_exist(hash_set_t hash_set, const void *element);

#endif /* HASH_SET_H_INCLUDED__ */
