/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** client_run
*/

#include "client.h"

char *clean_command(char *command)
{
    char *new_command = malloc(sizeof(char) * (strlen(command) + 1));
    int nb_char = 0;

    for (int i = 0; command[i]; i++) {
        if (command[i] == ' ' || command[i] == '\t' || command[i] == '\n' ||
            command[i] == '\r' || command[i] == '\v' || command[i] == '\f' ||
            command[i] == '"')
            continue;
        new_command[nb_char] = command[i];
        nb_char++;
    }
    new_command = realloc(new_command, sizeof(char) * (nb_char + 1));
    new_command[nb_char] = '\0';
    free(command);
    return new_command;
}

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

void client_read(client_t *client)
{
    printf("Reading...\n");
    int number_of_bytes = 0;

    read(client->socketFd, &number_of_bytes, 8);
    printf("Number of bytes: %d\n", number_of_bytes);
}

void client_run(client_t *client)
{
    char *input = NULL;
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(client->socketFd, &readfds);
    FD_SET(0, &readfds);

    while (1) {
        if (select(FD_SETSIZE, &readfds, NULL, NULL, NULL) == -1)
            break;
        if (FD_ISSET(client->socketFd, &readfds))
            client_read(client);
        if (FD_ISSET(0, &readfds))
            if (client_input_handling(&input, client))
                break;
    }
    free(input);
}
