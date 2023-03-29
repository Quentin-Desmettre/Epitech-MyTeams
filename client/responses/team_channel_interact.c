/*
** EPITECH PROJECT, 2023
** EPITECH_MYTEAMS_TEAM_CHANNEL_INTERACT_C
** File description:
** team_channel_interact.c
*/

#include "client.h"

void client_receiver_team_created_g(client_t *client)
{
    char *team_uuid = NULL;
    char *team_name = NULL;
    char *team_description = NULL;

    printf("team created_g\n");


    if (read_packet(client->buffer, "sss", &team_uuid, &team_name,
                &team_description))
        return;
    client_event_team_created(team_uuid, team_name, team_description);
}

void client_receiver_team_created_u(client_t *client)
{
    char *team_uuid = NULL;
    char *team_name = NULL;
    char *team_description = NULL;

    printf("team created\n");

    if (read_packet(client->buffer, "sss", &team_uuid, &team_name,
        &team_description))
        return;
    client_print_team_created(team_uuid, team_name, team_description);
}

void client_receiver_channel_created_g(client_t *client)
{
    char *channel_uuid = NULL;
    char *channel_name = NULL;
    char *channel_description = NULL;

    if (read_packet(client->buffer, "sss", &channel_uuid, &channel_name,
                &channel_description))
        return;
    client_event_channel_created(channel_uuid, channel_name, channel_description);
}

void client_receiver_channel_created_u(client_t *client)
{
    char *channel_uuid = NULL;
    char *channel_name = NULL;
    char *channel_description = NULL;

    if (read_packet(client->buffer, "sss", &channel_uuid, &channel_name,
                &channel_description))
        return;
    client_print_channel_created(channel_uuid, channel_name, channel_description);
}
