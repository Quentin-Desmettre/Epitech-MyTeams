/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** subscribed
*/
#include "server.h"

static void list_subscribed_teams(server_t *server, client_t *client)
{
    void *packet = create_packet(EV_LIST_TEAMS, NULL, NULL, 0);
    team_t *t;
    list_t *users;

    for (int i = 0; i < server->teams->size; i++) {
        t = server->teams->elems[i].value;
        if (!(users = t->users))
            continue;
        do {
            if (strcmp(users->data, client->user->uuid) == 0) {
                append_arg_to_packet(&packet, t->uuid, 17);
                append_arg_to_packet(&packet, t->name, strlen(t->name) + 1);
                append_arg_to_packet(&packet,
                                t->description, strlen(t->description) + 1);
                break;
            }
            users = users->next;
        } while (users != t->users);
    }
    send_packet(packet, client->fd, true);
}

void add_user_info(void **packet, char *uuid, server_t *server)
{
    int status;
    user_t *user = map_get(server->users_by_uuid, uuid);

    if (!user)
        return;
    status = map_get(server->clients_by_uuid, uuid) ? 1 : 0;
    append_arg_to_packet(packet, uuid, 17);
    append_arg_to_packet(packet, user->name, strlen(user->name) + 1);
    append_arg_to_packet(packet, &status, sizeof(int));
}

static void list_subscribed_users(server_t *server, client_t *client,
                                    char **args)
{
    void *packet;
    team_t *t = map_get(server->teams, args[0]);
    list_t *users = t ? t->users : NULL;

    if (!t)
        return send_error(client, UNKNOWN_TEAM, args[0]);
    packet = create_packet(EV_LIST_USERS, NULL, NULL, 0);
    if (!users)
        return send_packet(packet, client->fd, true);
    do {
        add_user_info(&packet, users->data, server);
        users = users->next;
    } while (users != t->users);
    send_packet(packet, client->fd, true);
}

void subscribed_handler(server_t *server, client_t *client, char **args)
{
    if (!args[0][0])
        list_subscribed_teams(server, client);
    else
        list_subscribed_users(server, client, args);
}
