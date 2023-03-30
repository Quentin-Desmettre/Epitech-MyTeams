/*
** EPITECH PROJECT, 2023
** EPITECH_MYTEAMS_CONNECTION_RECEIVER_C
** File description:
** connection_receiver.c
*/

#include "client.h"

void client_receiver_logged_in(client_t *client)
{
    char *uuid = NULL;
    char *username = NULL;

    if (!read_packet(client->buffer, "ss", &uuid, &username))
        return;
    client_event_logged_in(uuid, username);
}

void client_receiver_logged_out(client_t *client)
{
    char *uuid = NULL;
    char *username = NULL;

    if (!read_packet(client->buffer, "ss", &uuid, &username))
        return;
    client_event_logged_out(uuid, username);
}
