/*
** EPITECH PROJECT, 2023
** EPITECH_MYTEAMS_INFOS_C
** File description:
** infos.c
*/

#include "client.h"

void client_users(client_t *client, char **args)
{
    void *packet = create_packet(USERS, NULL, NULL, 0);
    send_packet(packet, client->socketFd, true);
}

void client_user(client_t *client, char **args)
{
    void *packet = create_packet(USER, NULL, NULL, 0);
    append_arg_to_packet(&packet, args[1],
        strlen(args[1]) + 1);
    send_packet(packet, client->socketFd, true);
}

void client_list(client_t *client, char **args)
{
    void *packet = create_packet(LIST, NULL, NULL, 0);
    send_packet(packet, client->socketFd, true);
}

void client_info(client_t *client, char **args)
{
    void *packet = create_packet(INFO, NULL, NULL, 0);
    send_packet(packet, client->socketFd, true);
}

void client_help(client_t *client, char **args)
{
    void *packet = create_packet(HELP, NULL, NULL, 0);
    send_packet(packet, client->socketFd, true);
}
