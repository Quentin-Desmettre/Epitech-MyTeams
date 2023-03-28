/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** client_input
*/

#include "client.h"
#include "math.h"

void get_string(char ***args, int opened_quotes, int length, char cpy)
{
    int tmp;

    if (length == -1) {
        tmp = ceil(opened_quotes / 2) + 1;
        (*args) = realloc((*args), sizeof(char *) * (tmp + 2));
        (*args)[tmp] = realloc((*args)[tmp], 1);
        (*args)[tmp][0] = '\0';
        (*args)[tmp + 1] = NULL;
        return;
    }
    tmp = ceil(opened_quotes / 2) + 1;
    (*args) = realloc((*args), sizeof(char *) * (tmp + 2));
    (*args)[tmp] = realloc((*args)[tmp], length + 2);
    (*args)[tmp][length] = cpy;
    (*args)[tmp][length + 1] = '\0';
    (*args)[tmp + 1] = NULL;
}

int opened_quote_handling(char ***args, int *length, int *opened_quotes,
    char next)
{
    (*opened_quotes)++;
    (*length) = 0;

    if (next == '"') {
        get_string(args, *opened_quotes, -1, 0);
        return 1;
    }
    if ((*opened_quotes) % 2 != 0)
        return 1;
    return 0;
}

int in_quotes_handling(char ***args, int *length, int opened_quotes, char act)
{
    if (opened_quotes % 2 == 0) {
        if (act == ' ' || act == '\t' || act == '\n' ||
            act == '\r' || act == '\v' || act == '\f' || act == '"')
            return 0;
        else {
            printf("Invalid character '%c' in quotes.\n", act);
            free_str_array(*args);
            return -1;
        }
    }
    get_string(args, opened_quotes, (*length), act);
    (*length) += 1;
    return 0;
}

char **get_args(char *input, int *opened_quotes)
{
    char **args = calloc(sizeof(char *), 2);
    int length = 0;

    for (int i = 0; input[i]; i++) {
        if (input[i] == '"' &&
            opened_quote_handling(&args, &length, opened_quotes, input[i + 1]))
            continue;
        if (!(*opened_quotes)) {
            args[0] = realloc(args[0], i + 2);
            args[0][i] = input[i];
            args[0][i + 1] = '\0';
            continue;
        }
        if (in_quotes_handling(&args, &length,
            (*opened_quotes), input[i]) == -1)
            return NULL;
    }
    return args;
}

void client_input(client_t *client)
{
    int number_quotes = 0;
    char **args = get_args(client->input_buffer, &number_quotes);

    client->input_args = args;
    if (!args)
        return;
    if (number_quotes % 2 != 0) {
        printf("Invalid number of quotes.\n");
        free_str_array(args);
        client->input_args = NULL;
        return;
    }
}