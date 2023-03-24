/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** login_out
*/

#include "server.h"

void login_handler(server_t *server, client_t *client, char **args)
{
    user_t *user = map_get(server->users_by_name, args[0]);
    int args_len[2];
    const void *args_ptr[2];

    if (!user) {
        user = malloc(sizeof(user_t));
        uuid_generate((unsigned char *)user->uuid);
        strcpy(user->name, args[0]);
        server_event_user_created(user->uuid, user->name);
    }
    server_event_user_logged_in(user->uuid);
    client->logged_in = true;
    map_add(server->clients_by_uuid, user->uuid, client);
    args_ptr[0] = user->uuid;
    args_len[0] = 17;
    args_ptr[1] = user->name;
    args_len[1] = strlen(user->name) + 1;
    send_packet(create_packet(EV_LOGGED_IN,
    args_ptr, args_len, 2), client->fd, true);
}

void logout_handler(server_t *server, client_t *client, UNUSED char **args)
{
    user_t *user = client->user;
    int args_len[2];
    const void *args_ptr[2];

    client->logged_in = false;
    args_ptr[0] = user->uuid;
    args_len[0] = 17;
    args_ptr[1] = user->name;
    args_len[1] = strlen(user->name) + 1;
    map_remove(server->clients_by_uuid, user->uuid);
    server_event_user_logged_out(user->uuid);
    send_packet(create_packet(EV_LOGGED_OUT, args_ptr, args_len, 2),
                client->fd, true);
}
