/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** user
*/

#include "server.h"

void user_handler(server_t *server, client_t *client, char **args)
{
    user_t *user = map_get(server->users_by_uuid, args[0]);
    int connected =
            (user && map_get(server->clients_by_uuid, args[0])) ? 1 : 0;

    if (!user)
        return send_error(client, UNKNOWN_USER, args[0]);
    send_packet(create_packet(EV_USER_INFO,
        (const void *[]){user->uuid, user->name, &connected},
        (const int []){17, strlen(user->name) + 1,
        sizeof(int)}, 3), client->fd);
}

void users_handler(server_t *server, client_t *client, UNUSED char **args)
{
    void *packet = create_packet(EV_LIST_USERS, NULL, NULL, 0);
    int connected = 0;

    for (int i = 0; i < server->users_by_uuid->size; i++) {
        append_arg_to_packet(&packet,
            server->users_by_uuid->elems[i].key, 16);
        append_arg_to_packet(&packet, server->users_by_uuid->elems[i].value,
            strlen(server->users_by_uuid->elems[i].value));
        connected = (map_get(server->clients_by_uuid,
            server->users_by_uuid->elems[i].key) ? 1 : 0);
        append_arg_to_packet(&packet, &connected, sizeof(int));
    }
    send_packet(packet, client->fd);
}
