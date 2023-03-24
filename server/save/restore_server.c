/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** restore_server
*/

#include "server.h"

static void restore_thread(channel_t *channel, int file)
{
    thread_t *thread = malloc(sizeof(thread_t));
    thread_message_t *message;
    int nb_replies = 0;

    read(file, thread->uuid, sizeof(thread->uuid));
    read(file, thread->title, sizeof(thread->title));
    read(file, thread->message, sizeof(thread->message));
    read(file, &thread->timestamp, sizeof(time_t));
    read(file, &nb_replies, sizeof(int));
    thread->replies = NULL;
    for (int i = 0; i < nb_replies; i++) {
        message = malloc(sizeof(thread_message_t));
        read(file, message->uuid_sender, sizeof(message->uuid_sender));
        read(file, message->content, sizeof(message->content));
        read(file, &message->timestamp, sizeof(time_t));
        append_node(&thread->replies, message);
    }
    map_add(channel->threads, thread->uuid, thread);
}

static void restore_channel(team_t *team, int file)
{
    channel_t *channel = malloc(sizeof(channel_t));
    int nb_threads;

    read(file, channel->uuid, sizeof(channel->uuid));
    read(file, channel->name, sizeof(channel->name));
    read(file, &channel->description, sizeof(channel->description));
    read(file, &nb_threads, sizeof(int));
    channel->threads = map_create((compare_key_t)uuid_compare, free_thread);
    for (int i = 0; i < nb_threads; i++)
        restore_thread(channel, file);
    map_add(team->channels, channel->uuid, channel);
}

static void restore_team(server_t *server, int file)
{
    team_t *team = malloc(sizeof(team_t));
    int nb_channels = 0;
    int subscribed_users;
    char uuid[sizeof(team->uuid)];

    read(file, team->uuid, sizeof(team->uuid));
    read(file, team->name, sizeof(team->name));
    read(file, team->description, sizeof(team->description));
    read(file, &nb_channels, sizeof(int));
    team->channels = map_create((compare_key_t)uuid_compare,
                                (free_value_t)free_channel);
    for (int i = 0; i < nb_channels; i++)
        restore_channel(team, file);
    read(file, &subscribed_users, sizeof(int));
    team->users = NULL;
    for (int i = 0; i < subscribed_users; i++) {
        read(file, uuid, sizeof(uuid));
        append_node(&team->users, memdup(uuid, sizeof(uuid)));
    }
    map_add(server->teams, team->uuid, team);
}

static void restore_message(server_t *server, int file)
{
    user_message_t *message = malloc(sizeof(user_message_t));
    void *key = malloc(sizeof(message->uuid_sender)
            + sizeof(message->uuid_receiver));

    read(file, message, sizeof(user_message_t));
    memcpy(key, message->uuid_sender, sizeof(message->uuid_sender));
    memcpy(key + sizeof(message->uuid_sender),
        message->uuid_receiver, sizeof(message->uuid_receiver));
    map_add(server->messages, key, message);
}

void restore_server(server_t *server)
{
    int file = open("server.db", O_RDONLY);
    int nb = 0;
    user_t *user;

    if (file < 0)
        return;
    read(file, &nb, sizeof(int));
    for (int i = 0; i < nb; i++)
        restore_team(server, file);
    read(file, &nb, sizeof(int));
    for (int i = 0; i < nb; i++) {
        user = malloc(sizeof(user_t));
        read(file, user, sizeof(user_t));
        server_event_user_loaded(user->uuid, user->name);
        map_add(server->users_by_uuid, user->uuid, user);
        map_add(server->users_by_name, user->name, user);
    }
    read(file, &nb, sizeof(int));
    for (int i = 0; i < nb; i++)
        restore_message(server, file);
}
