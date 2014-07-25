#include "hash_set.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COMMAND_EXIT   "exit"
#define COMMAND_ADD    "add"
#define COMMAND_REMOVE "remove"
#define COMMAND_COUNT  "count"
#define COMMAND_EXIST  "exist"

#define BUFFER_SIZE 124

char word_1[BUFFER_SIZE];
char word_2[BUFFER_SIZE];

void get_command(void)
{
    int ch, i;
    
    word_1[0] = '\0';
    word_2[0] = '\0';

    i = 0;
    while ((ch = getchar()) != ' ')
    {
        if (ch == '\n')
        {
            word_1[i] = '\0';
            return;
        }
        word_1[i++] = ch;
    }
    word_1[i] = '\0';

    i = 0;
    while ((ch = getchar()) != ' ')
    {
        if (ch == '\n')
        {
            word_2[i] = '\0';
            return;
        }
        word_2[i++] = ch;
    }
    word_2[i] = '\0';

    while ((ch = getchar()) != '\n');
}

int cmp(const void *e1, const void *e2)
{
    return strcmp(e1, e2) == 0;
}

uint32_t hash(const void *element)
{
    return dgb2_hash_str(element);
}

int main(int argc, char *argv[])
{
    hash_set_t set;

    set = hash_set_new(cmp, hash);

    if (!set)
    {
        fputs("Runtime error: can not allocate memory for hash set!", stderr);
        abort();
    }

    printf("Input command '%s' to exit.\n", COMMAND_EXIT);
    printf("Input command '%s element' to add element to the set.\n", COMMAND_ADD);
    printf("Input command '%s element' to remove element from the set.\n", COMMAND_REMOVE);
    printf("Input command '%s element' to check existence of element in the set.\n", COMMAND_EXIST);
    printf("Input command '%s' to print total number of elements in the set.\n", COMMAND_COUNT);

    while (1)
    {
        printf("command > ");
        get_command();

        if (strcmp(word_1, COMMAND_EXIT) == 0)
        {
            hash_set_free(&set);
            return EXIT_SUCCESS;
        }
        else if (strcmp(word_1, COMMAND_ADD) == 0)
        {
            size_t element_length;
            int result;
            void *element;

            element_length = strlen(word_2);

            if (0 == element_length)
            {
                puts("Element can not be zero length!");
                continue;
            }

            element = malloc(element_length + 1);

            if (!element)
            {
                fputs("Runtime error: can not allocate memory for new element!", stderr);
                abort();
            }

            strcpy(element, word_2);
            result = hash_set_add(set, element);
            
            switch (result)
            {
            case HASH_SET_BAD_ALLOC:
                fputs("Runtime error: can not allocate memory for new entry in hash set!", stderr);
                abort();
                break;
            case HASH_SET_ELEMENT_EXIST:
                printf("Element '%s' already exist in the hash set.\n", word_2);
                free(element);
                break;
            case HASH_SET_SUCCESS:
                printf("Element '%s' added into hash set.\n", word_2);
                break;
            }
        }
        else if (strcmp(word_1, COMMAND_REMOVE) == 0)
        {
            void *element = NULL;

            if (strlen(word_2) == 0)
            {
                puts("Element can not be zero length!");
                continue;
            }

            element = (void *) hash_set_remove(set, word_2);
            
            if (element)
            {
                printf("Element '%s' removed from hash set.\n", (const char *) element);
                free(element);
            }
            else
            {
                printf("Element '%s' does not exist in hash set.\n", word_2);
            }
        }
        else if (strcmp(word_1, COMMAND_COUNT) == 0)
        {
            int cnt = (int) hash_set_size(set);
            printf("Hash set has %d elements.\n", cnt);
        }
        else if (strcmp(word_1, COMMAND_EXIST) == 0)
        {
            if (strlen(word_2) == 0)
            {
                puts("Element can not be zero length!");
                continue;
            }

            if (hash_set_exist(set, word_2))
            {
                printf("Element '%s' exists in the hash set.\n", word_2);
            }
            else
            {
                printf("Element '%s' does not exist in the hash set.\n", word_2);
            }
        }
        else
        {
            printf("Can not recognize command '%s'!\n", word_1);
        }
    }

    return EXIT_SUCCESS;
}
