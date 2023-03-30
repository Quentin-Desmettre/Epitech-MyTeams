/*
** EPITECH PROJECT, 2023
** EPITECH_MYTEAMS_REPLY_C
** File description:
** reply.c
*/

#include "client.h"

void client_receiver_list_replies(client_t *client)
{

}

void client_receiver_help(client_t *client)
{
    char *body = NULL;

    if (!read_packet(client->buffer, "s", &body))
        return;
    printf("%s\n", body);
}

void client_receiver_message_received(client_t *client)
{
    char *user_uuid = NULL;
    char *body = NULL;

    if (!read_packet(client->buffer, "ss", &user_uuid, &body))
        return;
    client_event_private_message_received(user_uuid, body);
}

void client_receiver_reply_created_g(UNUSED client_t *client)
{
    return;
}

void client_receiver_reply_created_u(UNUSED client_t *client)
{
    return;
}
