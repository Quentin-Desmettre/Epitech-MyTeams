/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** responses_list
*/

#include "client.h"

void client_receiver_list_threads(client_t *client)
{
    list_t *packets = read_packet_list(client->buffer, "sstss");
    list_t *it = packets;
    char *uuid;
    char *uuid_creator;
    time_t timestamp;
    char *title;
    char *message;

    if (!packets)
        return;
    do {
        if (!read_packet(it->data, "sstss", &uuid, &uuid_creator,
            &timestamp, &title, &message))
            return;
        client_channel_print_threads(uuid,
        uuid_creator, timestamp, title, message);
        it = it->next;
    } while ((it != packets));
}

void client_receiver_list_messages(client_t *client)
{
    list_t *packets = read_packet_list(client->buffer, "sts");
    list_t *it = packets;
    char *uuid;
    time_t timestamp;
    char *content;

    if (!packets)
        return;
    do {
        if (!read_packet(it->data, "sts", &uuid, &timestamp, &content))
            return;
        client_private_message_print_messages(uuid, timestamp, content);
        it = it->next;
    } while ((it != packets));
}

void client_receiver_list_users(client_t *client)
{
    list_t *packets = read_packet_list(client->buffer, "ssi");
    list_t *it = packets;
    char *uuid;
    char *name;
    int status;

    if (!packets)
        return;
    do {
        if (!read_packet(it->data, "ssi", &uuid, &name, &status))
            return;
        client_print_users(uuid, name, status);
        it = it->next;
    } while ((it != packets));
}

void client_receiver_list_teams(client_t *client)
{
    list_t *packets = read_packet_list(client->buffer, "sss");
    list_t *it = packets;
    char *uuid;
    char *name;
    char *description;

    if (!packets)
        return;
    do {
        if (!read_packet(it->data, "sss", &uuid, &name, &description))
            return;
        client_print_teams(uuid, name, description);
        it = it->next;
    } while ((it != packets));
}

void client_receiver_list_channels(client_t *client)
{
    list_t *packets = read_packet_list(client->buffer, "sss");
    list_t *it = packets;
    char *uuid;
    char *name;
    char *description;

    if (!packets)
        return;
    do {
        if (!read_packet(it->data, "sss", &uuid, &name, &description))
            return;
        client_team_print_channels(uuid, name, description);
        it = it->next;
    } while ((it != packets));
}
