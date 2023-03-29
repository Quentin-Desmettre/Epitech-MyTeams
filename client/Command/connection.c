/*
** EPITECH PROJECT, 2023
** EPITECH_MYTEAMS_CONNECTION_C
** File description:
** connection.c
*/

#include "client.h"

void client_login(client_t *client, char **args)
{
    void *packet = create_packet(LOGIN, NULL, NULL, 0);
    append_arg_to_packet(&packet, args[1],
        strlen(args[1]) + 1);
    send_packet(packet, client->socketFd, true);
}

void client_logout(client_t *client, char **args)
{
    void *packet = create_packet(LOGOUT, NULL, NULL, 0);
    send_packet(packet, client->socketFd, true);
}
