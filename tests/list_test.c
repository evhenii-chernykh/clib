#include "list.h"

#include <stdio.h>
#include <stdlib.h>

void print_list(list_t list)
{
    putchar('[');
    for (; list; list = list->tail)
    {
        printf("%s", (const char *) list->head);
        if (list->tail)
        {
            printf(", ");
        }
    }
    putchar(']');
}

int main(int argc, char *argv[])
{
    list_t list_1, list_2, list_3;

    list_1 = list_list("first", "second", "third", NULL);
    list_2 = list_copy(list_1);

    printf("First list: ");
    print_list(list_1);
    putchar('\n');

    printf("Second list (copy of first list): ");
    print_list(list_2);
    putchar('\n');

    list_3 = list_append(list_1, list_2);

    printf("Third list (append second list to first list): ");
    print_list(list_3);
    putchar('\n');

    printf("Length of third list: %d\n", (int) list_length(list_3));

    list_free(&list_3);

    return EXIT_SUCCESS;
}
