/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** client_run
*/

#include "client.h"

void client_run(client_t *client)
{
    char *input = NULL;
    size_t input_size = 0;
    ssize_t input_len = 0;

    while (1) {
        input_len = getline(&input, &input_size, stdin);
        if (input_len == -1)
            break;
        input[input_len - 1] = '\0';
        client->input_buffer = input;
        client->input_buffer_size = input_size;
        client_input(client);
    }
    free(input);
}

