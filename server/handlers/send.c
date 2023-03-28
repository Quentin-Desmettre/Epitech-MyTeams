/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** send
*/

#include "server.h"

char *get_uuid_pair(const char *uuid_1, const char *uuid_2)
{
    char *uuid_pair = calloc(sizeof(char) * (UUID_LENGTH * 2 + 1), 1);
    const char *first = uuid_1;
    const char *second = uuid_2;

    if (strcmp((char *)uuid_1, (char *)uuid_2) > 0) {
        first = uuid_2;
        second = uuid_1;
    }
    memcpy(uuid_pair, first, UUID_LENGTH);
    memcpy(uuid_pair + UUID_LENGTH, second, UUID_LENGTH);
    return uuid_pair;
}

void send_handler(server_t *server, client_t *client, char **args)
{
    char *uuid_pair;
    client_t *dest_cli;
    void *packet;

    if (!map_get(server->users_by_uuid, args[0]))
        return send_error(client, UNKNOWN_USER, args[0]);
    uuid_pair = get_uuid_pair(client->user->uuid, args[0]);
    map_add(server->messages, uuid_pair, strdup(args[1]));
    server_event_private_message_sended(client->user->uuid, args[0], args[1]);
    dest_cli = map_get(server->clients_by_uuid, args[0]);
    if (!dest_cli)
        return;
    packet = create_packet(EV_MESSAGE_RECEIVED, NULL, NULL, 0);
    append_arg_to_packet(&packet, client->user->uuid, sizeof(client->user->uuid));
    send_packet(packet, dest_cli->fd, true);
}
