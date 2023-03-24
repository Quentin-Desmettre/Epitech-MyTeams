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
    const void *args_ptr[3];
    int args_len[3];

    if (!user)
        return send_error(client, UNKNOWN_USER, args[0]);
    args_ptr[0] = user->uuid;
    args_len[0] = 17;
    args_ptr[1] = user->name;
    args_len[1] = strlen(user->name) + 1;
    args_ptr[2] = &connected;
    args_len[2] = sizeof(int);
    send_packet(create_packet(EV_USER_INFO,
        args_ptr, args_len, 3), client->fd, true);
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
    send_packet(packet, client->fd, true);
}
