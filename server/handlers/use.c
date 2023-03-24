/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** use
*/

#include "server.h"

void use_handler(server_t *server, client_t *client, char **args)
{
    team_t *t = map_get(server->teams, args[0]);
    channel_t *c = t ? map_get(t->channels, args[1]) : NULL;
    thread_t *th = c ? map_get(c->threads, args[2]) : NULL;

    if (!t && strlen(args[0]) > 0)
        return send_error(client, UNKNOWN_TEAM, args[0]);
    if (!c && strlen(args[1]) > 0)
        return send_error(client, UNKNOWN_CHANNEL, args[1]);
    if (!th && strlen(args[2]) > 0)
        return send_error(client, UNKNOWN_THREAD, args[2]);
    client->context.team = t;
    client->context.channel = c;
    client->context.thread = th;
}
