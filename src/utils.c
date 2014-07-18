#include "utils.h"

uint32_t dgb2_hash(const void *data, size_t length)
{
    uint32_t hash = 5381;
    size_t i;
    const char *p = data;

    for (i = 0; i < length; i++)
    {
        hash = ((hash << 5) + hash) + p[i];
    }

    return hash;
}

uint32_t dgb2_hash_str(const char *str)
{
    uint32_t hash = 5381;
    int c;

    while (c = *str++)
    {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}
