#include "list_stack.h"

#include <assert.h>
#include <stddef.h>

struct list_stack_type
{
};

list_stack_t list_stack_new(void)
{
    return NULL;
}

int list_stack_empty(list_stack_t stack)
{
    assert(stack);
    return 0;
}

void list_stack_push(list_stack_t stack, void * data)
{
    assert(stack);
}

void * list_stack_pop(list_stack_t stack)
{
    assert(stack);
    return NULL;
}

void list_stack_free(list_stack_t * stack)
{
    assert(stack);
}
