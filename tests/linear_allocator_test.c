#include "linear_allocator.h"

#include <stdio.h>
#include <stdlib.h>

#define ALLOCATED_MEMORY_SIZE 100
#define CHUNK_SIZE 23

int main(int argc, char *argv[])
{
    linear_allocator_t allocator;
    void *mem;

    allocator = linear_allocator_new(ALLOCATED_MEMORY_SIZE);

    while (mem = linear_allocator_alloc(allocator, CHUNK_SIZE))
    {
        printf("Memory chunk size %d allocated at adress %p\n", CHUNK_SIZE, mem);
    }

    puts("Memory out, dealocating allocator");

    linear_allocator_free(&allocator);

    return EXIT_SUCCESS;
}
