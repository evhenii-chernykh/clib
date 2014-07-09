/*
 * Atom interface.
 */

#ifndef ATOM_H_INCLUDED__
#define ATOM_H_INCLUDED__

#include <stddef.h>

extern const char *atom_add(const char *str);

extern void atom_remove(const char *str);

extern int atom_count();

extern int atom_exist(const char *str);

extern void atom_free();

#endif /* ATOM_H_INCLUDED__ */
