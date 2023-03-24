/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** subscribe
*/

#include "server.h"

void subscribe_handler(server_t *server, client_t *client, char **args)
{
    team_t *t = map_get(server->teams, args[0]);

    if (!t)
        return send_error(client, UNKNOWN_TEAM, args[0]);
    append_node(&t->users, client->user->uuid);
    server_event_user_subscribed(args[0], client->user->uuid);
}

void unsubscribe_handler(server_t *server, client_t *client, char **args)
{
    team_t *t = map_get(server->teams, args[0]);
    list_t *user = t ? t->users : NULL;
    int index = 0;

    if (!t || !user)
        return send_error(client, UNKNOWN_TEAM, args[0]);
    do {
        if (strcmp(user->data, client->user->uuid) == 0)
            break;
        user = user->next;
        index++;
    } while (user != t->users);
    if (index != 0 && user == t->users)
        return send_error(client, UNAUTHORIZED, "");
    remove_node(&t->users, index, NULL);
    server_event_user_unsubscribed(args[0], client->user->uuid);
}
