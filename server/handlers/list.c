/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** list
*/

#include "server.h"

static void list_teams(server_t *server, client_t *client)
{
    void *packet = create_packet(EV_LIST_TEAMS, NULL, NULL, 0);
    map_elem_t *elem = server->teams->elems;
    team_t *team;

    for (int i = 0; i < server->teams->size; i++) {
        team = elem[i].value;
        append_arg_to_packet(&packet, team->uuid, sizeof(team->uuid));
        append_arg_to_packet(&packet, team->name, sizeof(team->name));
        append_arg_to_packet(&packet, team->description,
        sizeof(team->description));
    }
    send_packet(packet, client->fd, true);
}

static void list_channels(client_t *client)
{
    void *packet = create_packet(EV_LIST_CHANNELS, NULL, NULL, 0);
    map_elem_t *elem = client->context.team->channels->elems;
    channel_t *channel;

    for (int i = 0; i < client->context.team->channels->size; i++) {
        channel = elem[i].value;
        append_arg_to_packet(&packet, channel->uuid, sizeof(channel->uuid));
        append_arg_to_packet(&packet, channel->name, sizeof(channel->name));
        append_arg_to_packet(&packet, channel->description,
        sizeof(channel->description));
    }
    send_packet(packet, client->fd, true);
}

static void list_threads(client_t *client)
{
    void *packet = create_packet(EV_LIST_THREADS, NULL, NULL, 0);
    map_elem_t *elem = client->context.channel->threads->elems;
    thread_t *thread;

    for (int i = 0; i < client->context.channel->threads->size; i++) {
        thread = elem[i].value;
        append_arg_to_packet(&packet, thread->uuid, sizeof(thread->uuid));
        append_arg_to_packet(&packet, thread->uuid_creator,
        sizeof(thread->uuid_creator));
        append_arg_to_packet(&packet, &thread->timestamp, sizeof(time_t));
        append_arg_to_packet(&packet, thread->title, sizeof(thread->title));
        append_arg_to_packet(&packet, thread->message, sizeof(thread->message));
    }
    send_packet(packet, client->fd, true);
}

static void list_thread_replies(client_t *client)
{
    void *packet = create_packet(EV_LIST_REPLIES, NULL, NULL, 0);
    list_t *replies = client->context.thread->replies;
    thread_message_t *reply;
    const char *thread_uuid = client->context.thread->uuid;

    if (!replies)
        return send_packet(packet, client->fd, true);
    do {
        reply = replies->data;
        append_arg_to_packet(&packet, thread_uuid, sizeof(thread_uuid));
        append_arg_to_packet(&packet,
        reply->uuid_sender, sizeof(reply->uuid_sender));
        append_arg_to_packet(&packet, &reply->timestamp, sizeof(time_t));
        append_arg_to_packet(&packet, reply->content, sizeof(reply->content));
        replies = replies->next;
    } while (replies != client->context.thread->replies);
    send_packet(packet, client->fd, true);
}

void list_handler(server_t *server, client_t *client, UNUSED char **args)
{
    user_context_t *context = &client->context;

    if (!context->team)
        return list_teams(server, client);
    if (!context->channel)
        return list_channels(client);
    if (!context->thread)
        return list_threads(client);
    return list_thread_replies(client);
}
