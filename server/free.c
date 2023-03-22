/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** free
*/

#include "server.h"

void free_client(client_t *client)
{
    close(client->fd);
    free(client->buffer);
    free(client);
}

void free_message_list(list_t *messages)
{
    free_list(&messages, free);
}

// TODO: free team, thread, channel
void free_team(team_t *team)
{
}

void free_thread(void *th)
{
}

void free_channel(void *ch)
{
}
