#ifndef LIST_STACK_H_INCLUDED__
#define LIST_STACK_H_INCLUDED__

typedef struct list_stack_type * list_stack_t;

extern list_stack_t list_stack_new(void);

extern int list_stack_empty(list_stack_t stack);

extern void list_stack_push(list_stack_t stack, void * data);

extern void * list_stack_pop(list_stack_t stack);

extern void list_stack_free(list_stack_t * stack);

#endif /* LIST_STACK_H_INCLUDED__ */
