/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** user
*/

#include "server.h"

bool is_connected(server_t *server, char *uuid)
{
    return (map_get(server->clients_by_uuid, uuid) ? true : false);
}

void user_handler(server_t *server, client_t *client, char **args)
{
    user_t *user = map_get(server->users_by_uuid, args[0]);
    int connected =
            (user && is_connected(server, args[0])) ? 1 : 0;
    void *packet;

    if (!user)
        return send_error(client, UNKNOWN_USER, args[0]);
    packet = create_packet(EV_USER_INFO, NULL, NULL, 0);
    append_arg_to_packet(&packet, user->uuid, sizeof(user->uuid));
    append_arg_to_packet(&packet, user->name, strlen(user->name) + 1);
    append_arg_to_packet(&packet, &connected, sizeof(int));
    send_packet(packet, client->fd, true);
}

void users_handler(server_t *server, client_t *client, UNUSED char **args)
{
    void *packet = create_packet(EV_LIST_USERS, NULL, NULL, 0);
    int connected = 0;
    user_t *user;

    for (int i = 0; i < server->users_by_uuid->size; i++) {
        user = server->users_by_uuid->elems[i].value;
        append_arg_to_packet(&packet, user->uuid, R_UUID_LENGTH);
        append_arg_to_packet(&packet, user->name, strlen(user->name) + 1);
        connected = is_connected(server, server->users_by_uuid->elems[i].key);
        append_arg_to_packet(&packet, &connected, sizeof(int));
    }
    send_packet(packet, client->fd, true);
}
