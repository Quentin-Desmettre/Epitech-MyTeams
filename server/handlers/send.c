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

static user_message_t *create_message(client_t *client, char **args)
{
    user_message_t *message = calloc(sizeof(user_message_t), 1);
    memcpy(message->uuid_sender,
        client->user->uuid, sizeof(client->user->uuid));
    memcpy(message->uuid_receiver, args[0], strlen(args[0]));
    memcpy(message->content, args[1], strlen(args[1]));
    message->timestamp = time(NULL);
    return message;
}

static void append_message(server_t *server,
                            char *uuid_pair, user_message_t *message)
{
    list_t *message_list = map_get(server->messages, uuid_pair);
    append_node(&message_list, message);
    if (message_list->next == message_list)
        map_add(server->messages, uuid_pair, message_list);
    else
        free(uuid_pair);
}

void send_handler(server_t *server, client_t *client, char **args)
{
    char *uuid_pair;
    client_t *dest_cli;
    void *packet;

    if (!map_get(server->users_by_uuid, args[0]))
        return send_error(client, UNKNOWN_USER, args[0]);
    uuid_pair = get_uuid_pair(client->user->uuid, args[0]);
    append_message(server, uuid_pair, create_message(client, args));
    server_event_private_message_sended(client->user->uuid, args[0], args[1]);
    dest_cli = map_get(server->clients_by_uuid, args[0]);
    if (!dest_cli)
        return;
    packet = create_packet(EV_MESSAGE_RECEIVED, NULL, NULL, 0);
    append_arg_to_packet(&packet,
    client->user->uuid, sizeof(client->user->uuid));
    send_packet(packet, dest_cli->fd, true);
}
