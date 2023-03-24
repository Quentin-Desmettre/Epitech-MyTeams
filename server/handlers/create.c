/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** create
*/

#include "server.h"

void create_team(server_t *server, client_t *client,
                    const char *team_name, const char *team_desc)
{
    team_t *t;

    if (team_exists(team_name, server))
        return send_error(client, ALREADY_EXIST, "");
    t = calloc(sizeof(team_t), 1);
    generate_uuid(t->uuid);
    memcpy(t->name, team_name, strlen(team_name) + 1);
    memcpy(t->description, team_desc, strlen(team_desc) + 1);
    t->channels = map_create((compare_key_t)uuid_compare, free_channel);
    server_event_team_created(t->uuid, t->name, client->user->uuid);
    map_add(server->teams, t->uuid, t);
    notify_team_creation(t, server, client);
}

void create_channel(server_t *server, client_t *cli,
                    const char *ch_name, const char *ch_desc)
{
    channel_t *ch;

    if (!is_user_subscribed(cli, cli->context.team))
        return send_error(cli, UNAUTHORIZED, cli->context.team->name);
    if (channel_exists(ch_name, cli->context.team))
        return send_error(cli, ALREADY_EXIST, "");
    ch = calloc(sizeof(channel_t), 1);
    generate_uuid(ch->uuid);
    memcpy(ch->name, ch_name, strlen(ch_name) + 1);
    memcpy(ch->description, ch_desc, strlen(ch_desc) + 1);
    ch->threads = map_create((compare_key_t)uuid_compare, free_thread);
    server_event_channel_created(cli->context.team->uuid, ch->uuid, ch->name);
    map_add(cli->context.team->channels, ch->uuid, ch);
    notify_channel_creation(ch, server, cli);
}

void create_thread(server_t *server, client_t *cli,
                    const char *th_name, const char *th_desc)
{
    thread_t *th;

    if (!is_user_subscribed(cli, cli->context.team))
        return send_error(cli, UNAUTHORIZED, cli->context.team->name);
    if (thread_exists(th_name, cli->context.channel))
        return send_error(cli, ALREADY_EXIST, "");
    th = calloc(sizeof(thread_t), 1);generate_uuid(th->uuid);
    th->timestamp = clock() / CLOCKS_PER_SEC;
    memcpy(th->title, th_name, strlen(th_name) + 1);
    memcpy(th->message, th_desc, strlen(th_desc) + 1);
    memcpy(th->uuid_creator, cli->user->uuid, 17);
    server_event_thread_created(cli->context.channel->uuid, th->uuid,
    cli->user->uuid, th->title, th->message);
    map_add(cli->context.channel->threads, th->uuid, th);
    notify_thread_creation(th, server, cli);
}

void create_reply(server_t *server, client_t *cli, const char *re_msg)
{
    thread_message_t *re;

    if (!is_user_subscribed(cli, cli->context.team))
        return send_error(cli, UNAUTHORIZED, cli->context.team->name);
    re = calloc(sizeof(thread_message_t), 1);
    memcpy(re->uuid_sender, cli->user->uuid, 17);
    memcpy(re->content, re_msg, strlen(re_msg) + 1);
    re->timestamp = clock() / CLOCKS_PER_SEC;
    server_event_reply_created(cli->context.thread->uuid, re->uuid_sender,
    re->content);
    append_node(&cli->context.thread->replies, re);
    notify_thread_message_creation(re, server, cli);
}

void create_handler(server_t *server, client_t *client, char **args)
{
    if (client->context.team == NULL)
        return create_team(server, client, args[0], args[1]);
    if (client->context.channel == NULL)
        return create_channel(server, client, args[0], args[1]);
    if (client->context.thread == NULL)
        return create_thread(server, client, args[0], args[1]);
    create_reply(server, client, args[0]);
}
