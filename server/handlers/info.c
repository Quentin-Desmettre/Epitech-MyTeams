/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** info
*/

#include "server.h"

static void info_user(client_t *client)
{
    void *packet = create_packet(EV_USER_INFO, NULL, NULL, 0);
    int is_connected = 1;

    append_arg_to_packet(&packet,
    client->user->uuid, sizeof(client->user->uuid));
    append_arg_to_packet(&packet,
    client->user->name, sizeof(client->user->name));
    append_arg_to_packet(&packet, &is_connected, sizeof(int));
    send_packet(packet, client->fd, true);
}

static void info_team(server_t *s, client_t *client)
{
    team_t *team = map_get(s->teams, client->context.team);
    void *packet = create_packet(EV_TEAM_INFO, NULL, NULL, 0);

    append_arg_to_packet(&packet, team->uuid, sizeof(team->uuid));
    append_arg_to_packet(&packet, team->name, sizeof(team->name));
    append_arg_to_packet(&packet, team->description, sizeof(team->description));
    send_packet(packet, client->fd, true);
}

static void info_channel(server_t *s, client_t *client)
{
    team_t *team = map_get(s->teams, client->context.team);
    channel_t *channel = map_get(team->channels, client->context.channel);
    void *packet = create_packet(EV_CHANNEL_INFO, NULL, NULL, 0);

    append_arg_to_packet(&packet, channel->uuid, sizeof(channel->uuid));
    append_arg_to_packet(&packet, channel->name, sizeof(channel->name));
    append_arg_to_packet(&packet,
    channel->description, sizeof(channel->description));
    send_packet(packet, client->fd, true);
}

static void info_thread(server_t *s, client_t *client)
{
    team_t *team = map_get(s->teams, client->context.team);
    channel_t *channel = map_get(team->channels, client->context.channel);
    thread_t *thread = map_get(channel->threads, client->context.thread);
    void *packet = create_packet(EV_THREAD_INFO, NULL, NULL, 0);

    append_arg_to_packet(&packet, thread->uuid, sizeof(thread->uuid));
    append_arg_to_packet(&packet,
    thread->uuid_creator, sizeof(thread->uuid_creator));
    append_arg_to_packet(&packet, &thread->timestamp, sizeof(time_t));
    append_arg_to_packet(&packet, thread->title, sizeof(thread->title));
    append_arg_to_packet(&packet, thread->message, sizeof(thread->message));
    send_packet(packet, client->fd, true);
}

void info_handler(server_t *server, client_t *client, UNUSED char **args)
{
    user_context_t *context = &client->context;
    team_t *team = context->team ? map_get(server->teams, context->team) : 0;

    if (handle_context(server, client))
        return;
    if (context->team == NULL)
        return info_user(client);
    if (!is_user_subscribed(client, team))
        return send_error(client, UNAUTHORIZED, "");
    if (context->channel == NULL)
        return info_team(server, client);
    if (context->thread == NULL)
        return info_channel(server, client);
    return info_thread(server, client);
}
