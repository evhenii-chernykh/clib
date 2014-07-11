#ifndef ARENA_INCLUDED_H__
#define ARENA_INCLUDED_H__

struct arena_type;
typedef struct arena_type *arena_t;

extern arena_t arena_new(void);

extern void arena_free(arena_t *arena);

#endif /* ARENA_INCLUDED_H__ */
