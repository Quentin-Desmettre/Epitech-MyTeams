/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** responses_unknown
*/

#include "client.h"

void client_receiver_unknown_team(client_t *client)
{
    char *team_uuid;

    if (!read_packet(client->buffer, "s", &team_uuid))
        return;
    client_error_unknown_team(team_uuid);
}

void client_receiver_unknown_channel(client_t *client)
{
    char *channel_uuid;

    if (!read_packet(client->buffer, "s", &channel_uuid))
        return;
    client_error_unknown_channel(channel_uuid);
}

void client_receiver_unknown_thread(client_t *client)
{
    char *thread_uuid;

    if (!read_packet(client->buffer, "s", &thread_uuid))
        return;
    client_error_unknown_thread(thread_uuid);
}

void client_receiver_unknown_user(client_t *client)
{
    char *user_uuid;

    if (!read_packet(client->buffer, "s", &user_uuid))
        return;
    client_error_unknown_user(user_uuid);
}

void client_receiver_unknown_command(client_t *client)
{
    char *command;

    if (!read_packet(client->buffer, "s", &command))
        return;
    printf("Unknown command %s\n", command);
}
