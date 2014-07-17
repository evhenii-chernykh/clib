#include "list.h"

#include <stdarg.h>
#include <stdlib.h>

list_t list_list(void *first, ...)
{
    va_list ap;
    list_t head_node, last_node, current_node;
    void *value;

    if (!first)
    {
        return NULL;
    }

    head_node = malloc(sizeof(struct list_type));

    if (!head_node)
    {
        return NULL;
    }

    head_node->head = first;
    head_node->tail = NULL;
    last_node = head_node;

    va_start(ap, first);

    while (value = va_arg(ap, void *))
    {
        current_node = malloc(sizeof(struct list_type));

        if (!current_node)
        {
            list_free(&head_node);
            return NULL;
        }

        current_node->head = value;
        current_node->tail = NULL;
        last_node->tail = current_node;
        last_node = current_node;
    }

    va_end(ap);

    return head_node;
}

void list_free(list_t *list)
{
    list_t current, next;

    for (current = *list; current; current = next)
    {
        next = current->tail;
        free(current);
    }

    list = NULL;
}

list_t list_copy(list_t list)
{
    list_t result, last;

    if (!list)
    {
        return NULL;
    }
    
    result = malloc(sizeof(struct list_type));

    if (!result)
    {
        return NULL;
    }

    result->head = list->head;
    result->tail = NULL;
    last = result;
    list = list->tail;

    for (; list; list = list->tail)
    {
        last->tail = malloc(sizeof(struct list_type));
        if (!last->tail)
        {
            list_free(&result);
            return NULL;
        }
        last = last->tail;
        last->head = list->head;
        last->tail = NULL;
    }
    
    return result;
}

size_t list_length(list_t list)
{
    size_t result = 0;

    for(; list; list = list->tail)
    {
        result++;
    }

    return result;
}

list_t list_append(list_t list, list_t tail)
{
    list_t result = list;

    if (!list)
    {
        return tail;
    }

    for (; list->tail; list = list->tail);

    list->tail = tail;

    return result;
}
