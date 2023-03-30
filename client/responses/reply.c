/*
** EPITECH PROJECT, 2023
** EPITECH_MYTEAMS_REPLY_C
** File description:
** reply.c
*/

#include "client.h"

void client_receiver_list_replies(client_t *client)
{
    list_t *packets = read_packet_list(client->buffer, "ssts");
    list_t *it = packets;
    char *thread_uuid = NULL;
    char *user_uuid = NULL;
    time_t reply_timestamp = 0;
    char *reply_body = NULL;

    if (!packets)
        return;
    do {
        read_packet(it->data, "ssts", &thread_uuid, &user_uuid,
            &reply_timestamp, &reply_body);
        client_thread_print_replies(thread_uuid, user_uuid,
            reply_timestamp, reply_body);
        it = it->next;
    } while ((it != packets));
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
    char *team_uuid = NULL;
    char *thread_uuid = NULL;
    char *user_uuid = NULL;
    char *reply_body = NULL;

    read_packet(client->buffer, "ssss", &team_uuid, &thread_uuid,
        &user_uuid, &reply_body);
    client_event_thread_reply_received(team_uuid, thread_uuid, user_uuid,
        reply_body);
}

void client_receiver_reply_created_u(client_t *client)
{
    char *thread_uuid = NULL;
    char *user_uuid = NULL;
    time_t reply_timestamp = 0;
    char *reply_body = NULL;

    read_packet(client->buffer, "ssts", &thread_uuid, &user_uuid,
        &reply_timestamp, &reply_body);
    client_print_reply_created(thread_uuid, user_uuid, reply_timestamp,
        reply_body);
}
