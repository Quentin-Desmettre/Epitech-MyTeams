/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** send
*/

#include "server.h"

char *get_uuid_pair(const char *uuid_1, const char *uuid_2)
{
    char *uuid_pair = malloc(sizeof(char) * (UUID_LENGTH * 2));
    const char *first = uuid_1;
    const char *second = uuid_2;

    if (uuid_compare((unsigned char *)uuid_1, (unsigned char *)uuid_2) > 0) {
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
    const void *args_ptr[2];
    int args_len[2];

    if (!map_get(server->users_by_uuid, args[0]))
        return send_error(client, UNKNOWN_USER, args[0]);
    uuid_pair = get_uuid_pair(client->user->uuid, args[0]);
    map_add(server->messages, uuid_pair, strdup(args[1]));
    server_event_private_message_sended(client->user->uuid, args[0], args[1]);
    dest_cli = map_get(server->clients_by_uuid, args[0]);
    if (!dest_cli)
        return;
    args_ptr[0] = client->user->uuid;
    args_len[0] = 17;
    args_ptr[1] = args[1];
    args_len[1] = strlen(args[1]) + 1;
    send_packet(create_packet(EV_MESSAGE_RECEIVED,
        args_ptr, args_len, 2), dest_cli->fd, true);
}
