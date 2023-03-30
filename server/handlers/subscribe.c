/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** subscribe
*/

#include "server.h"

static void send_subscribe_data(const char *user_uuid, const char *team_uuid,
            int fd, enum responses code)
{
    void *packet = create_packet(code, NULL, NULL, 0);

    append_arg_to_packet(&packet, user_uuid, R_UUID_LENGTH);
    append_arg_to_packet(&packet, team_uuid, R_UUID_LENGTH);
    send_packet(packet, fd, true);
}

void subscribe_handler(server_t *server, client_t *client, char **args)
{
    team_t *t = map_get(server->teams, args[0]);

    if (!t)
        return send_error(client, UNKNOWN_TEAM, args[0]);
    if (is_user_subscribed(client, t))
        return;
    append_node(&t->users, client->user->uuid);
    server_event_user_subscribed(args[0], client->user->uuid);
    send_subscribe_data(client->user->uuid, args[0],
                        client->fd, USER_SUBSCRIBED);
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
    send_subscribe_data(client->user->uuid, args[0],
                        client->fd, USER_UNSUBSCRIBED);
}
