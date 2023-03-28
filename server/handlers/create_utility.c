/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** create2
*/

#include "server.h"

bool team_exists(const char *name, server_t *server)
{
    team_t *t;

    for (int i = 0; i < server->teams->size; i++) {
        t = server->teams->elems[i].value;
        if (strcmp(t->name, name) == 0)
            return true;
    }
    return false;
}

bool is_user_subscribed(client_t *cli, team_t *team)
{
    list_t *users = team->users;

    if (!users)
        return false;
    do {
        if (strcmp(users->data, cli->user->uuid) == 0)
            return true;
        users = users->next;
    } while (users != team->users);
    return false;
}

bool channel_exists(const char *name, team_t *team)
{
    channel_t *ch;

    for (int i = 0; i < team->channels->size; i++) {
        ch = team->channels->elems[i].value;
        if (strcmp(ch->name, name) == 0)
            return true;
    }
    return false;
}

bool thread_exists(const char *name, channel_t *channel)
{
    thread_t *th;

    for (int i = 0; i < channel->threads->size; i++) {
        th = channel->threads->elems[i].value;
        if (strcmp(th->title, name) == 0)
            return true;
    }
    return false;
}
