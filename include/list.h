#ifndef LIST_H_INCLUDED__
#define LIST_H_INCLUDED__

#include <stddef.h>

struct list_type;
typedef struct list_type *list_t;

struct list_type
{
    const void *head;
    list_t tail;
};

extern list_t list_list(void *first, ...);

extern void list_free(list_t *list);

extern list_t list_copy(list_t list);

extern size_t list_length(list_t list);

extern list_t list_append(list_t list, list_t tail);

#endif /* LIST_H_INCLUDED__ */
