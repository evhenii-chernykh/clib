#include "list_stack.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    list_stack_t stack = list_stack_new();

    list_stack_push(stack, "one");
    list_stack_push(stack, "two");
    list_stack_push(stack, "three");

    puts("list_stack_test!");

    while(!list_stack_empty(stack))
    {
        printf("stack pop: %s\n", (char *)list_stack_pop(stack));
    }

    list_stack_free(&stack);

    return EXIT_SUCCESS;
}
