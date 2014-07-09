#include "atom.h"

#include <stdio.h>
#include <string.h>

#define COMMAND_EXIT   "exit"
#define COMMAND_ADD    "add"
#define COMMAND_REMOVE "remove"
#define COMMAND_EXIST  "exist"
#define COMMAND_COUNT  "count"
#define COMMAND_FREE   "free"

char input_buffer[1024];

char command[1024];
char atom_value[1024];

void get_command(void)
{
    int ch, i;
    
    command[0] = '\0';
    atom_value[0] = '\0';

    i = 0;
    while ((ch = getchar()) != ' ')
    {
        if (ch == '\n')
        {
            command[i] = '\0';
            return;
        }
        command[i++] = ch;
    }
    command[i] = '\0';

    i = 0;
    while ((ch = getchar()) != ' ')
    {
        if (ch == '\n')
        {
            atom_value[i] = '\0';
            return;
        }
        atom_value[i++] = ch;
    }
    atom_value[i] = '\0';

    while ((ch = getchar()) != '\n');
}

int main(int argc, char *argv[])
{
    printf("Input command '%s' to exit.\n", COMMAND_EXIT);
    printf("Input command '%s atom' to add atom.\n", COMMAND_ADD);
    printf("Input command '%s atom' to remove atom.\n", COMMAND_REMOVE);
    printf("Input command '%s atom' to check existence of atom.\n", COMMAND_EXIST);
    printf("Input command '%s' to print total number of atoms.\n", COMMAND_COUNT);
    printf("Input command '%s' to free all atoms.\n", COMMAND_FREE);
    
    while (1)
    {
        printf("command > ");
        get_command();

        if (strcmp(command, COMMAND_EXIT) == 0)
        {
            return 0;
        }
        else if (strcmp(command, COMMAND_ADD) == 0)
        {
            const char *at = atom_add(atom_value);
            printf("Atom '%s' was added at adress %p, atom value = '%s'.\n", atom_value, (void *)at, at);
        }
        else if (strcmp(command, COMMAND_REMOVE) == 0)
        {
            if (atom_exist(atom_value))
            {
                atom_remove(atom_value);
                printf("Atom '%s' was removed.\n", atom_value);
            }
            else
            {
                printf("Atom '%s' does not exist.\n", atom_value);
            }
        }
        else if (strcmp(command, COMMAND_EXIST) == 0)
        {
            if (atom_exist(atom_value))
            {
                printf("Atom '%s' exists.\n", atom_value);
            }
            else
            {
                printf("Atom '%s' does not exist.\n", atom_value);
            }
        }
        else if (strcmp(command, COMMAND_COUNT) == 0)
        {
            printf("Total number of atoms = %d.\n", atom_count(atom_value));
        }
        else if (strcmp(command, COMMAND_FREE) == 0)
        {
            atom_free();
            printf("All atoms was removed.\n");
        }
        else if (strlen(command) != 0)
        {
            printf("Command does not exist!\n");
        }
    }

    return 0;
}
