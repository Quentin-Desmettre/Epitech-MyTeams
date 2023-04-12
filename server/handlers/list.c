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

static void list_channels(server_t *s, client_t *client)
{
    team_t *t = map_get(s->teams, client->context.team);
    void *packet = create_packet(EV_LIST_CHANNELS, NULL, NULL, 0);
    map_elem_t *elem = t->channels->elems;
    channel_t *channel;

    for (int i = 0; i < t->channels->size; i++) {
        channel = elem[i].value;
        append_arg_to_packet(&packet, channel->uuid, sizeof(channel->uuid));
        append_arg_to_packet(&packet, channel->name, sizeof(channel->name));
        append_arg_to_packet(&packet, channel->description,
        sizeof(channel->description));
    }
    send_packet(packet, client->fd, true);
}

static void list_threads(server_t *s, client_t *client)
{
    team_t *t = map_get(s->teams, client->context.team);
    channel_t *c = map_get(t->channels, client->context.channel);
    void *packet = create_packet(EV_LIST_THREADS, NULL, NULL, 0);
    map_elem_t *elem = c->threads->elems;
    thread_t *thread;

    for (int i = 0; i < c->threads->size; i++) {
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

static void list_thread_replies(server_t *s, client_t *client)
{
    team_t *team = map_get(s->teams, client->context.team);
    channel_t *channel = map_get(team->channels, client->context.channel);
    thread_t *thread = map_get(channel->threads, client->context.thread);
    void *packet = create_packet(EV_LIST_REPLIES, NULL, NULL, 0);
    list_t *replies = thread->replies;
    thread_message_t *reply;
    const char *thread_uuid = thread->uuid;

    if (!replies)
        return send_packet(packet, client->fd, true);
    do {
        reply = replies->data;
        append_arg_to_packet(&packet, thread_uuid, sizeof(thread_uuid));
        append_arg_to_packet(&packet, reply->uuid_sender, sizeof(reply->uuid_sender));
        append_arg_to_packet(&packet, &reply->timestamp, sizeof(time_t));
        append_arg_to_packet(&packet, reply->content, sizeof(reply->content));
        replies = replies->next;
    } while (replies != thread->replies);
    send_packet(packet, client->fd, true);
}

void list_handler(server_t *server, client_t *client, UNUSED char **args)
{
    user_context_t *context = &client->context;
    team_t *t = context->team ? map_get(server->teams, context->team) : NULL;

    if (handle_context(server, client))
        return;
    if (!context->team)
        return list_teams(server, client);
    if (!is_user_subscribed(client, t))
        return send_error(client, UNAUTHORIZED, "");
    if (!context->channel)
        return list_channels(server, client);
    if (!context->thread)
        return list_threads(server, client);
    return list_thread_replies(server, client);
}
