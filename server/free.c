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

void free_team(team_t *team)
{
    free_list(&team->users, free);
    map_destroy(team->channels);
    free(team);
}

void free_channel(void *ch)
{
    map_destroy(((channel_t *)ch)->threads);
    free(ch);
}

void free_thread(void *th)
{
    free_list(&((thread_t *)th)->replies, free);
    free(th);
}
