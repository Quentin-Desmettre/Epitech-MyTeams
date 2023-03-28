/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** client_input
*/

#include "client.h"
#include "math.h"

bool check_args(char **args)
{
}

char **get_args(char *input)
{
    char **args = calloc(sizeof(char *), 2);
    int opened_quotes = 0;
    int length = 0;
    int tmp = 0;

    for (int i = 0; input[i]; i++) {
        if (input[i] == '"') {
            opened_quotes++;
            length = 0;
            if (input[i + 1] == '"') {
                tmp = ceil(opened_quotes / 2) + 1;
                args = realloc(args, sizeof(char *) * (tmp + 2));
                args[tmp] = realloc(args[tmp], 1);
                args[tmp][length] = '\0';
                args[tmp + 1] = NULL;
                continue;
            }
            if (opened_quotes % 2 != 0)
                continue;
        }
        if (!opened_quotes) {
            args[0] = realloc(args[0], i + 2);
            args[0][i] = input[i];
            args[0][i + 1] = '\0';
        } else {
            if (opened_quotes % 2 == 0)
                continue;
            tmp = ceil(opened_quotes / 2) + 1;
            args = realloc(args, sizeof(char *) * (tmp + 2));
            args[tmp] = realloc(args[tmp], length + 2);
            args[tmp][length] = input[i];
            args[tmp][length + 1] = '\0';
            args[tmp + 1] = NULL;
            length += 1;
        }
    }
    for (int i = 0; args[i]; i++) {
        printf("%s\n", args[i]);
    }

    if (opened_quotes % 2 != 0) {
        printf("Invalid number of quotes.\n");
        free_str_array(args);
        return NULL;
    }
}

void client_input(client_t *client)
{
    char **args = get_args(client->input_buffer);

    if (!check_args(args)) {
        printf("Invalid arguments.\n");
        return;
    }
}