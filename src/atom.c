#include "atom.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define BUCKET_NUM 2048

static struct atom
{
    struct atom *link;
    char *str;
    unsigned long hash;
} *buckets[BUCKET_NUM];

static int atom_cnt = 0;

static unsigned long dgb2_hash(const unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c;

    return hash;
}

int atom_exist(const char *str)
{
    unsigned long hash;
    struct atom *p;

    assert(str);

    hash = dgb2_hash(str) % BUCKET_NUM;

    for (p = buckets[hash]; p; p = p->link)
    {
        if (hash == p->hash && (strcmp(str, p->str) == 0))
        {
            return 1;
        }
    }

    return 0;
}

const char *atom_add(const char *str)
{
    unsigned long hash;
    struct atom *p;

    assert(str);

    hash = dgb2_hash(str) % BUCKET_NUM;

    for (p = buckets[hash]; p; p = p->link)
    {
        if (hash == p->hash && (strcmp(str, p->str) == 0))
        {
            return p->str;
        }
    }

    p = malloc(sizeof(struct atom));
    
    if (!p)
    {
        return NULL;
    }

    p->str = malloc(strlen(str) + 1);

    if (!p->str)
    {
        free(p);
        return NULL;
    }

    strcpy(p->str, str);
    p->link = buckets[hash];
    p->hash = hash;
    buckets[hash] = p;
    atom_cnt++;

    return p->str;
}

void atom_remove(const char *str)
{
    unsigned long hash;
    struct atom *p, *t;

    assert(str);

    hash = dgb2_hash(str) % BUCKET_NUM;
    p = buckets[hash];
    buckets[hash] = NULL;

    for (; p; p = t)
    {
        t = p->link;
        if (hash == p->hash && (strcmp(str, p->str) == 0))
        {
            free(p->str);
            free(p);
            atom_cnt--;
        }
        else
        {
            p->link = buckets[hash];
            buckets[hash] = p;
        }
    }
}

int atom_count()
{
    return atom_cnt;
}

void atom_free()
{
    struct atom *p, *t;
    size_t i;

    for (i = 0; i < BUCKET_NUM; i++)
    {
        for (p = buckets[i]; p; p = t)
        {
            t = p->link;
            free(p->str);
            free(p);
        }
        buckets[i] = NULL;
    }

    atom_cnt = 0;
}
