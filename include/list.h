#ifndef LIST_H_INCLUDED__
#define LIST_H_INCLUDED__

struct list_type;
typedef struct list_type *list_t;

struct list_type
{
    void *head;
    list_t tail;
};

extern list_t list_list(void *first, ...);

extern void list_free(list_t *list);

#endif /* LIST_H_INCLUDED__ */
