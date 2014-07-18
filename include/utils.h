#ifndef UTILS_H_INCLUDED__
#define UTILS_H_INCLUDED__

#include <stddef.h>
#include <stdint.h>

extern uint32_t dgb2_hash(const void *data, size_t length);

extern uint32_t dgb2_hash_str(const char *str);

#endif /* UTILS_H_INCLUDED__ */
