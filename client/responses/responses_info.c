/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** responses_info
*/

#include "client.h"

void client_receiver_list_replies(client_t *client)
{

}

void client_receiver_user_info(client_t *client)
{
    char *uuid;
    char *name;
    int is_connected;

    read_packet(client->buffer, "ssi", &uuid, &name, &is_connected);
    client_print_user(uuid, name, is_connected);
}

void client_receiver_team_info(client_t *client)
{
    char *uuid;
    char *name;
    char *description;

    read_packet(client->buffer, "sss", &uuid, &name, &description);
    client_print_team(uuid, name, description);
}

void client_receiver_channel_info(client_t *client)
{
    char *uuid;
    char *name;
    char *description;

    read_packet(client->buffer, "sss", &uuid, &name, &description);
    client_print_channel(uuid, name, description);
}

void client_receiver_thread_info(client_t *client)
{
    char *thread_uuid;
    char *uuid_sender;
    time_t timestamp;
    char *title;
    char *body;

    read_packet(client->buffer, "sstss", &thread_uuid,
        &uuid_sender, &timestamp, &title, &body);
    client_print_thread(thread_uuid, uuid_sender, timestamp, title, body);
}
