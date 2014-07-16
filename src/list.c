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
