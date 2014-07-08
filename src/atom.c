#include "atom.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define BUCKET_NUM 2048

static struct atom
{
    struct atom *link;
    size_t length;
    char *str;
} *buckets[BUCKET_NUM];

static unsigned long dgb2_hash(const unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c;

    return hash;
}

const char *atom_string(const char *str)
{
    unsigned long hash;
    size_t i, len;
    struct atom *p;

    assert(str);

    hash = dgb2_hash(str) % BUCKET_NUM;
    len = strlen(str);

    for (p = buckets[hash]; p; p = p->link)
    {
        if (len == p->length)
        {
            if (strcmp(str, p->str) == 0)
                return p->str;
        }
    }

    p = malloc(sizeof(struct atom));
    
    if (!p)
    {
        return NULL;
    }

    p->str = malloc(len + 1);

    if (!p->str)
    {
        free(p);
        return NULL;
    }

    strcpy(p->str, str);
    p->link = buckets[hash];
    p->length = len;
    buckets[hash] = p;

    return p->str;
}

size_t atom_length(const char *str)
{
    unsigned long hash;
    struct atom *p;

    assert(str);

    hash = dgb2_hash(str) % BUCKET_NUM;
    
    for (p = buckets[hash]; p; p = p->link)
    {
        if (str == p->str)
            return p->length;
    }

    assert(0);

    return 0;
}
