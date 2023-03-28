/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** client_run
*/

#include "client.h"

void client_command_handling(client_t *client)
{
    void *packet = create_packet(LOGIN, NULL, NULL, 0);
    printf("%s\n", client->input_args[1]);
    printf("%d\n", strlen(client->input_args[1]) + 1);
    append_arg_to_packet(&packet, client->input_args[1],
        strlen(client->input_args[1]) + 1);
    send_packet(packet, client->socketFd, true);
}

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
        if (client->input_args) {
            client_command_handling(client);
            free_str_array(client->input_args);
        }
    }
    free(input);
}
