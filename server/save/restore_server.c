/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** restore_server
*/

#include "server.h"

static void restore_thread(channel_t *channel, int file)
{
    thread_t *thread = calloc(1, sizeof(thread_t));
    thread_message_t *mess;
    int nb_replies = 0;

    read(file, thread->uuid, sizeof(thread->uuid));
    read(file, thread->title, sizeof(thread->title));
    read(file, thread->message, sizeof(thread->message));
    read(file, &thread->timestamp, sizeof(time_t));
    read(file, &nb_replies, sizeof(int));
    thread->replies = NULL;
    for (int i = 0; i < nb_replies; i++) {
        mess = calloc(1, sizeof(thread_message_t));
        read(file, mess->uuid_sender, sizeof(mess->uuid_sender));
        read(file, mess->content, sizeof(mess->content));
        read(file, &mess->timestamp, sizeof(time_t));
        append_node(&thread->replies, mess);
        printf("Reply restored: %s (%s)\n", mess->content, mess->uuid_sender);
    }
    map_add(channel->threads, thread->uuid, thread);
    printf("Thread restored: %s (%s)\n", thread->title, thread->uuid);
}

static void restore_channel(team_t *team, int file)
{
    channel_t *channel = calloc(1, sizeof(channel_t));
    int nb_threads;

    read(file, channel->uuid, sizeof(channel->uuid));
    read(file, channel->name, sizeof(channel->name));
    read(file, &channel->description, sizeof(channel->description));
    read(file, &nb_threads, sizeof(int));
    channel->threads = map_create((compare_key_t)strcmp, free_thread);
    for (int i = 0; i < nb_threads; i++)
        restore_thread(channel, file);
    map_add(team->channels, channel->uuid, channel);
    printf("Channel restored: %s (%s)\n", channel->name, channel->uuid);
}

void restore_team(server_t *server, int file)
{
    team_t *team = calloc(1, sizeof(team_t));
    int nb_channels = 0;
    int subscribed_users;
    char uuid[sizeof(team->uuid)];
    read(file, team->uuid, sizeof(team->uuid));
    read(file, team->name, sizeof(team->name));
    read(file, team->description, sizeof(team->description));
    read(file, &nb_channels, sizeof(int));
    team->channels = map_create((compare_key_t)strcmp,
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
    printf("Team restored: %s (%s)\n", team->name, team->uuid);
}

void restore_message_list(server_t *server, int file)
{
    char *uuid_pair = calloc(UUID_PAIR_LEN, 1);
    int nb_messages;
    user_message_t *mess;
    list_t *list = NULL;

    read(file, uuid_pair, UUID_PAIR_LEN);
    read(file, &nb_messages, sizeof(int));
    for (int i = 0; i < nb_messages; i++) {
        mess = calloc(1, sizeof(user_message_t));
        read(file, mess, sizeof(user_message_t));
        append_node(&list, mess);
        printf("Message restored: %s (%s -> %s)\n",
        mess->content, mess->uuid_sender, mess->uuid_receiver);
    }
    map_add(server->messages, uuid_pair, list);
}

void restore_server(server_t *server)
{
    int file = open("server.db", O_RDONLY);
    int nb = 0;
    user_t *user;
    uint64_t magic_number;

    if (file < 0)
        return;
    read(file, &magic_number, sizeof(uint64_t));
    if (magic_number != MAGIC_NUMBER)
        return (void)close(file);
    read(file, &nb, sizeof(int));
    for (int i = 0; i < nb; i++) {
        user = calloc(sizeof(user_t), 1);
        read(file, user, sizeof(user_t));
        server_event_user_loaded(user->uuid, user->name);
        map_add(server->users_by_uuid, user->uuid, user);
        map_add(server->users_by_name, user->name, user);
    }
    restore_messages_and_teams(file, server);
}
