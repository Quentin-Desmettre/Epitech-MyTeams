/*
** EPITECH PROJECT, 2023
** EPITECH_MYTEAMS_INTERRACTION_C
** File description:
** interraction.c
*/

#include "client.h"

void client_send(client_t *client, char **args)
{
    void *packet = create_packet(SEND, NULL, NULL, 0);

    append_arg_to_packet(&packet, args[1], strlen(args[1]) + 1);
    append_arg_to_packet(&packet, args[2], strlen(args[2]) + 1);
    send_packet(packet, client->socketFd, true);
}

void client_messages(client_t *client, char **args)
{
    void *packet = create_packet(MESSAGES, NULL, NULL, 0);

    append_arg_to_packet(&packet, args[1], strlen(args[1]) + 1);
    send_packet(packet, client->socketFd, true);
}

void client_subscribe(client_t *client, char **args)
{
    void *packet = create_packet(SUBSCRIBE, NULL, NULL, 0);

    append_arg_to_packet(&packet, args[1], strlen(args[1]) + 1);
    send_packet(packet, client->socketFd, true);
}

void client_subscribed(client_t *client, char **args)
{
    void *packet = create_packet(SUBSCRIBED, NULL, NULL, 0);

    if (!args[1])
        append_arg_to_packet(&packet, "", 1);
    else
        append_arg_to_packet(&packet, args[1], strlen(args[1]) + 1);
    send_packet(packet, client->socketFd, true);
}

void client_unsubscribe(client_t *client, char **args)
{
    void *packet = create_packet(UNSUBSCRIBE, NULL, NULL, 0);

    append_arg_to_packet(&packet, args[1], strlen(args[1]) + 1);
    send_packet(packet, client->socketFd, true);
}
