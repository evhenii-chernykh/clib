/*
 * Linked list stack adt implementation.
 */

#include "list_stack.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

struct list_stack_element
{
    void *value;
    struct list_stack_element *next;
};

struct list_stack_type
{
    int count;
    struct list_stack_element *head;
};

list_stack_t list_stack_new(void)
{
    struct list_stack_type *stack = malloc(sizeof(struct list_stack_type));

    if (stack)
    {
        stack->count = 0;
        stack->head = NULL;
    }

    return stack;
}

int list_stack_empty(list_stack_t stack)
{
    assert(stack);

    return stack->count == 0;
}

void list_stack_push(list_stack_t stack, void * data)
{
    struct list_stack_element *element;

    assert(stack);

    element = malloc(sizeof(struct list_stack_element));

    if (element)
    {
        element->value = data;
        element->next = stack->head;
        stack->head = element;
        stack->count++;
    }
}

void * list_stack_pop(list_stack_t stack)
{
    struct list_stack_element *element;
    void *value;

    assert(stack);
    assert(stack->count > 0);

    element = stack->head;
    value = element->value;
    stack->head = element->next;
    stack->count--;

    free(element);

    return value;
}

void list_stack_free(list_stack_t *stack)
{
    struct list_stack_element *element, *next_element;

    assert(stack && *stack);

    for (element = (*stack)->head; element != NULL; element = next_element)
    {
        next_element = element->next;
        free(element);
    }

    free(*stack);

    stack = NULL;
}
