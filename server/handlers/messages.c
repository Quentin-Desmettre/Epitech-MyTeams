/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** messages
*/

#include "server.h"

void add_message_to_packet(void **packet, user_message_t *msg)
{
    append_arg_to_packet(packet, msg->uuid_sender, 17);
    append_arg_to_packet(packet, &msg->timestamp, sizeof(time_t));
    append_arg_to_packet(packet, msg->content, strlen(msg->content) + 1);
}

void messages_handler(server_t *server, client_t *client, char **args)
{
    user_t *other_user = map_get(server->users_by_uuid, args[0]);
    char *uuid_pair;
    void *packet;
    list_t *messages;
    list_t *head;

    if (!other_user)
        return send_error(client, UNKNOWN_USER, args[0]);
    uuid_pair = get_uuid_pair(client->user->uuid, args[0]);
    packet = create_packet(EV_LIST_MESSAGES, NULL, NULL, 0);
    head = map_get(server->messages, uuid_pair);
    free(uuid_pair);
    messages = head;
    if (!messages)
        return send_packet(packet, client->fd, true);
    do {
        add_message_to_packet(&packet, messages->data);
        messages = messages->next;
    } while (messages != head);
    send_packet(packet, client->fd, true);
}
