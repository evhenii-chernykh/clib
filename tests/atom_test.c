#include "atom.h"

#include <stdio.h>

char input_buffer[1024];

int main(int argc, char *argv[])
{
    puts("atom test!");

    while (strcmp(input_buffer, "exit"))
    {
        scanf("%s", input_buffer);
        atom_string(input_buffer);
    }

    return 0;
}
