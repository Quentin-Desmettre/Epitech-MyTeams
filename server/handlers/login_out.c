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
    printf("login_handler\n");
    void *packet;

    if (!user) {
        user = calloc(sizeof(user_t), 1);
        generate_uuid(user->uuid);
        strcpy(user->name, args[0]);
        server_event_user_created(user->uuid, user->name);
        map_add(server->users_by_name, user->name, user);
        map_add(server->users_by_uuid, user->uuid, user);
    }
    server_event_user_logged_in(user->uuid);
    client->logged_in = true;
    client->user = user;
    packet = create_packet(EV_LOGGED_IN, NULL, NULL, 0);
    append_arg_to_packet(&packet, user->uuid, sizeof(user->uuid));
    append_arg_to_packet(&packet, user->name, strlen(user->name) + 1);
    send_packet(packet, client->fd, true);
}

void logout_handler(server_t *server, client_t *client, UNUSED char **args)
{
    user_t *user = client->user;
    printf("logout_handler\n");
    void *packet = create_packet(EV_LOGGED_OUT, NULL, NULL, 0);

    append_arg_to_packet(&packet, user->uuid, sizeof(user->uuid));
    append_arg_to_packet(&packet, user->name, strlen(user->name) + 1);
    map_remove(server->clients_by_uuid, user->uuid);
    server_event_user_logged_out(user->uuid);
    printf("User %s logged out\n", user->name);
    send_packet(packet, client->fd, true);
}
