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

    if (!user) {
        user = malloc(sizeof(user_t));
        uuid_generate((unsigned char *)user->uuid);
        strcpy(user->name, args[0]);
        server_event_user_created(user->uuid, user->name);
    }
    server_event_user_logged_in(user->uuid);
    client->logged_in = true;
    map_add(server->clients_by_uuid, user->uuid, client);
    send_packet(create_packet(EV_LOGGED_IN,
    (const void *[]){user->uuid, user->name},
    (const int []){17, strlen(user->name) + 1}, 2), client->fd);
}

void logout_handler(server_t *server, client_t *client, UNUSED char **args)
{
    user_t *user = client->user;

    client->logged_in = false;
    map_remove(server->clients_by_uuid, user->uuid);
    server_event_user_logged_out(user->uuid);
    send_packet(create_packet(EV_LOGGED_OUT,
    (const void *[]){user->uuid, user->name},
    (const int []){17, strlen(user->name) + 1}, 2), client->fd);
}
