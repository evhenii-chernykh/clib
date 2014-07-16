#ifndef ARENA_INCLUDED_H__
#define ARENA_INCLUDED_H__

#include <stddef.h>

struct linear_allocator_type;
typedef struct linear_allocator_type *linear_allocator_t;

extern linear_allocator_t linear_allocator_new(size_t heap_size);

extern void linear_allocator_free(linear_allocator_t *allocator);

extern void *linear_allocator_alloc(linear_allocator_t allocator, size_t size);

extern size_t linear_allocator_size(linear_allocator_t allocator);

extern size_t linear_allocator_avail(linear_allocator_t allocator);

#endif /* ARENA_INCLUDED_H__ */
