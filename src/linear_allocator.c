#include "linear_allocator.h"

#include <assert.h>
#include <stdlib.h>

union align
{
    char c;
    short s;
    int i;
    long l;
    float f;
    double d;
    long double ld;
    void *vp;
    void (*fp)(void);
};

#define CHUNK_SIZE sizeof(union align)

struct linear_allocator_type
{
    size_t heap_size;
    union align *memory;
    union align *current;
    union align *end;
};

linear_allocator_t linear_allocator_new(size_t heap_size)
{
    struct linear_allocator_type *allocator;
    size_t quot, rem, num_of_chunks, aligned_size;

    assert(heap_size);

    allocator = malloc(sizeof(struct linear_allocator_type));

    if (!allocator)
    {
        return NULL;
    }

    quot = heap_size / CHUNK_SIZE;
    rem = heap_size % CHUNK_SIZE;
    num_of_chunks = rem ? (quot + 1) : quot;
    aligned_size = num_of_chunks * CHUNK_SIZE;
    allocator->memory = malloc(aligned_size);

    if (!allocator->memory)
    {
        free(allocator);
        return NULL;
    }

    allocator->heap_size = aligned_size;
    allocator->current = allocator->memory;
    allocator->end = allocator->memory + num_of_chunks;

    return allocator;
}

void linear_allocator_free(linear_allocator_t *allocator)
{
    assert(allocator && *allocator);

    free((*allocator)->memory);
    free(*allocator);
    allocator = NULL;
}

void *linear_allocator_alloc(linear_allocator_t allocator, size_t size)
{
    size_t quot, rem, aligned_size;
    union align *old_position;

    assert(allocator);

    quot = size / CHUNK_SIZE;
    rem = size % CHUNK_SIZE;
    aligned_size = rem ? (quot + 1) : quot;

    if (allocator->current + aligned_size > allocator->end)
    {
        return NULL;
    }

    old_position = allocator->current;
    allocator->current += aligned_size;

    return old_position;
}
