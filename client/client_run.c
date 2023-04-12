/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** client_run
*/

#include "client.h"

void client_command_handling(client_t *client)
{
    client->input_args[0] = clean_command(client->input_args[0]);

    for (int i = 0; COMMANDS[i].name; i++)
        if (strcmp(COMMANDS[i].name, client->input_args[0]) == 0
            && COMMANDS[i].min_args <= client->arg_count
            && COMMANDS[i].max_args >= client->arg_count) {
            printf("Command found\n");
            COMMANDS[i].func(client, client->input_args);
            return;
        }
}

int client_input_handling(char **input, client_t *client)
{
    size_t input_size = 0;
    ssize_t input_len = 0;

    write(1, "> ", 2);
    input_len = getline(input, &input_size, stdin);
    if (input_len == -1)
        return EXIT_FAILURE;
    (*input)[input_len - 1] = '\0';
    client->input_buffer = (*input);
    client->input_buffer_size = input_size;
    client_input(client);
    if (client->input_args) {
        client_command_handling(client);
        free_str_array(client->input_args);
    }
    return EXIT_SUCCESS;
}

void client_run(client_t *client)
{
    char *input = NULL;
    fd_set readfds;

    while (1) {
        FD_ZERO(&readfds);
        FD_SET(client->socketFd, &readfds);
        FD_SET(0, &readfds);
        if (select(FD_SETSIZE, &readfds, NULL, NULL, NULL) == -1)
            break;
        if (FD_ISSET(client->socketFd, &readfds) && client_read(client))
            break;
        if (FD_ISSET(0, &readfds) && client_input_handling(&input, client))
            break;
    }
    free(input);
}
