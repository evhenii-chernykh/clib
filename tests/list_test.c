#include "list.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    list_t list, current, next;

    list = list_list("first", "second", "third", NULL);

    putchar('[');

    for (current = list; current; current = current->tail)
    {
        printf("%s", (const char *) current->head);
        if (current->tail)
        {
            printf(", ");
        }
    }

    puts("]");

    list_free(&list);

    return EXIT_SUCCESS;
}
