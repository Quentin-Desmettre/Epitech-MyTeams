/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** login_out
*/

#include "server.h"

static user_t *generate_user(server_t *server, char **args)
{
    user_t *user = calloc(sizeof(user_t), 1);

    generate_uuid(user->uuid);
    strcpy(user->name, args[0]);
    server_event_user_created(user->uuid, user->name);
    map_add(server->users_by_name, user->name, user);
    map_add(server->users_by_uuid, user->uuid, user);
    return user;
}

void login_handler(server_t *server, client_t *client, char **args)
{
    user_t *user = map_get(server->users_by_name, args[0]); void *packet;

    if (client->user)
        logout_handler(server, client, NULL);
    if (strlen(args[0]) > MAX_NAME_LENGTH)
        return send_error(client, UNAUTHORIZED, NULL);
    if (!user)
        user = generate_user(server, args);
    if (!map_get(server->clients_by_uuid, user->uuid)) {
        map_add(server->clients_by_uuid, user->uuid, client);
        client->is_in_uuid_map = true;
    }
    server_event_user_logged_in(user->uuid);
    client->logged_in = true;client->user = user;
    packet = create_packet(EV_LOGGED_IN, NULL, NULL, 0);
    append_arg_to_packet(&packet, user->uuid, sizeof(user->uuid));
    append_arg_to_packet(&packet, user->name, strlen(user->name) + 1);
    send_packet(packet, client->fd, true);
}

void logout_handler(server_t *server, client_t *client, UNUSED char **args)
{
    user_t *user = client->user;
    void *packet = create_packet(EV_LOGGED_OUT, NULL, NULL, 0);

    append_arg_to_packet(&packet, user->uuid, sizeof(user->uuid));
    append_arg_to_packet(&packet, user->name, strlen(user->name) + 1);
    server_event_user_logged_out(user->uuid);
    send_packet(packet, client->fd, true);
    client->logged_in = false;
    client->user = NULL;
    if (client->is_in_uuid_map)
        map_remove(server->clients_by_uuid, user->uuid);
}
