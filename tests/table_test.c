#include "table.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COMMAND_EXIT   "exit"
#define COMMAND_ADD    "add"
#define COMMAND_REMOVE "remove"
#define COMMAND_GET    "get"
#define COMMAND_COUNT  "count"
#define COMMAND_EXIST  "exist"

#define BUFFER_SIZE 124

char word_1[BUFFER_SIZE];
char word_2[BUFFER_SIZE];
char word_3[BUFFER_SIZE];

uint32_t hash(const void *key)
{
    return dgb2_hash_str(key);
}

int cmp(const void *key1, const void *key2)
{
    return strcmp(key1, key2) == 0;
}

void get_command(void)
{
    int ch, i;
    
    word_1[0] = '\0';
    word_2[0] = '\0';
    word_3[0] = '\0';

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

    i = 0;
    while ((ch = getchar()) != ' ')
    {
        if (ch == '\n')
        {
            word_3[i] = '\0';
            return;
        }
        word_3[i++] = ch;
    }
    word_3[i] = '\0';

    while ((ch = getchar()) != '\n');
}

int main(int argc, char *argv[])
{
    table_t table = table_new(cmp, hash);

    if (!table)
    {
        fprintf(stderr, "Runtime error: can not allocate table!\n");
        abort();
    }

    printf("Input command '%s' to exit.\n", COMMAND_EXIT);
    printf("Input command '%s key value' to add key->value pair.\n", COMMAND_ADD);
    printf("Input command '%s key' to remove key->value pair.\n", COMMAND_REMOVE);
    printf("Input command '%s key' to check existence of key->value pair.\n", COMMAND_EXIST);
    printf("Input command '%s' to print total number of key->value pairs.\n", COMMAND_COUNT);

    while (1)
    {
        printf("command > ");
        get_command();

        if (strcmp(word_1, COMMAND_EXIT) == 0)
        {
            table_free(&table);
            return EXIT_SUCCESS;
        }
        else if (strcmp(word_1, COMMAND_ADD) == 0)
        {
            size_t key_length, value_length;
            void *k, *v, *old_v;

            old_v = NULL;
            key_length = strlen(word_2);
            value_length = strlen(word_3);

            if (0 == key_length)
            {
                puts("Key can not be empty!");
                continue;
            }

            if (0 == value_length)
            {
                puts("Value can not be empty!");
                continue;
            }

            k = malloc(key_length + 1);

            if (!k)
            {
                fprintf(stderr, "Runtime error: can not allocate memory for key!\n");
                abort();
            }

            v = malloc(value_length + 1);

            if (!v)
            {
                fprintf(stderr, "Runtime error: can not allocate memory for value!\n");
                free(v);
                abort();
            }

            strcpy(k, word_2);
            strcpy(v, word_3);

            if (table_add(table, k, v, &old_v) == TABLE_BAD_ALLOC)
            {
                fprintf(stderr, "Runtime error: cannot allocate memory for new entry in table!\n");
                table_free(&table);
                abort();
            }

            printf("New ('%s', '%s') pair added in table", (const char *) k, (const char *) v);
            if (old_v)
            {
                printf(", old value of key '%s' was '%s'", (const char *) k, (const char *) old_v);
                free(old_v);
            }
            printf(".\n");
        }
        else if (strcmp(word_1, COMMAND_REMOVE) == 0)
        {
            void *old_value;

            if (strlen(word_2) == 0)
            {
                puts("Key can not be empty!");
                continue;
            }

            if (table_remove(table, word_2, &old_value) == TABLE_KEY_NOT_EXIST)
            {
                printf("Key '%s' does not exist.\n", word_2);
            }
            else
            {
                printf("Pair ('%s', '%s') removed from table.\n", word_2, (const char *) old_value);
                free(old_value);
            }
        }
        else if (strcmp(word_1, COMMAND_EXIST) == 0)
        {
            if (strlen(word_2) == 0)
            {
                puts("Key can not be empty!");
                continue;
            }

            if (table_key_exists(table, word_2))
            {
                printf("Key '%s' exists in table.\n", word_2);
            }
            else
            {
                printf("Key '%s' does not exist in table.\n", word_2);
            }
        }
        else if (strcmp(word_1, COMMAND_COUNT) == 0)
        {
            int cnt = table_size(table);

            printf("Table has %d entryes.\n", cnt);
        }
        else if (strcmp(word_1, COMMAND_GET) == 0)
        {
            void *value;

            if (strlen(word_2) == 0)
            {
                puts("Key can not be empty!");
                continue;
            }

            if (table_get(table, word_2, &value) == TABLE_KEY_NOT_EXIST)
            {
                printf("Key '%s' does not exist in table.\n", word_2);
            }
            else
            {
                printf("Value = '%s'.\n", (const char *) value);
            }
        }
        else
        {
            printf("Can not recognize command '%s'!\n", word_1);
        }
    }

    return EXIT_SUCCESS;
}
