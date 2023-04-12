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

void append_to_list_in_map(map_t *map, char *key, void *data)
{
    list_t *list = map_get(map, key);

    if (!list)
        append_node(&list, data);
    else {
        append_node(&list, data);
        map_remove(map, key);
    }
    map_add(map, key, list);
}

void login_handler(server_t *server, client_t *client, char **args)
{
    user_t *user = map_get(server->users_by_name, args[0]); void *packet;
    list_t *cli;

    if (client->user)
        logout_handler(server, client, NULL);
    if (strlen(args[0]) > MAX_NAME_LENGTH)
        return send_error(client, UNAUTHORIZED, "");
    user = (user ? user : generate_user(server, args));
    append_to_list_in_map(server->clients_by_uuid, user->uuid, client);
    server_event_user_logged_in(user->uuid);
    client->logged_in = true;
    client->user = user;
    packet = create_packet(EV_LOGGED_IN, NULL, NULL, 0);
    append_arg_to_packet(&packet, user->uuid, sizeof(user->uuid));
    append_arg_to_packet(&packet, user->name, strlen(user->name) + 1);
    for (int i = 0; i < server->clients_by_uuid->size; i++) {
        cli = server->clients_by_uuid->elems[i].value;
        send_to_client_list(packet, cli, false);
    }
    free(packet);
}

static void remove_client_from_list(map_t *map, char *uuid, int client_fd)
{
    list_t *list = map_get(map, uuid);
    list_t * const head = list;
    client_t *cli;
    int index = 0;

    map_remove(map, uuid);
    do {
        cli = list->data;
        if (cli->fd == client_fd) {
            remove_node(&list, index, NULL);
            break;
        }
        index++;
        list = list->next;
    } while (list != head);
    if (list)
        map_add(map, uuid, list);
}

void logout_handler(server_t *server, client_t *client, UNUSED char **args)
{
    user_t *user = client->user;
    void *packet = create_packet(EV_LOGGED_OUT, NULL, NULL, 0);
    list_t *cli;

    append_arg_to_packet(&packet, user->uuid, sizeof(user->uuid));
    append_arg_to_packet(&packet, user->name, strlen(user->name) + 1);
    for (int i = 0; i < server->clients_by_uuid->size; i++) {
        cli = server->clients_by_uuid->elems[i].value;
        send_to_client_list(packet, cli, false);
    }
    free(packet);
    server_event_user_logged_out(user->uuid);
    client->logged_in = false;
    client->user = NULL;
    remove_client_from_list(server->clients_by_uuid, user->uuid, client->fd);
}
