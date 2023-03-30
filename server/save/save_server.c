/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** save_server
*/

#include "server.h"

static void save_thread(thread_t *thread, int file)
{
    int nb_replies = list_size(thread->replies);
    list_t *elem = thread->replies;
    thread_message_t *message;

    write(file, thread->uuid, sizeof(thread->uuid));
    write(file, thread->title, sizeof(thread->title));
    write(file, thread->message, sizeof(thread->message));
    write(file, &thread->timestamp, sizeof(time_t));
    write(file, &nb_replies, sizeof(int));
    for (int i = 0; i < nb_replies; i++, elem = elem->next) {
        message = elem->data;
        write(file, message->uuid_sender, sizeof(message->uuid_sender));
        write(file, message->content, sizeof(message->content));
        write(file, &message->timestamp, sizeof(time_t));
    }
}

static void save_channel(channel_t *channel, int file)
{
    write(file, channel->uuid, sizeof(channel->uuid));
    write(file, channel->name, sizeof(channel->name));
    write(file, channel->description, sizeof(channel->description));
    write(file, &channel->threads->size, sizeof(int));
    for (int i = 0; i < channel->threads->size; i++)
        save_thread(channel->threads->elems[i].value, file);
}

static void save_team(team_t *team, int file)
{
    int subscribed_users = list_size(team->users);
    list_t *elem;

    write(file, team->uuid, sizeof(team->uuid));
    write(file, team->name, sizeof(team->name));
    write(file, team->description, sizeof(team->description));
    write(file, &team->channels->size, sizeof(int));
    for (int i = 0; i < team->channels->size; i++)
        save_channel(team->channels->elems[i].value, file);
    write(file, &subscribed_users, sizeof(int));
    elem = team->users;
    for (int i = 0; i < subscribed_users; i++) {
        write(file, elem->data, sizeof(team->uuid));
        elem = elem->next;
    }
}

static void save_message_list(const char *uuid_pair, list_t *messages, int fd)
{
    int nb_messages = list_size(messages);
    list_t *elem = messages;
    user_message_t *message;

    write(fd, uuid_pair, UUID_PAIR_LEN);
    write(fd, &nb_messages, sizeof(int));
    for (int i = 0; i < nb_messages; i++, elem = elem->next) {
        message = elem->data;
        write(fd, message, sizeof(user_message_t));
    }
}

void save_server(server_t *server)
{
    int file = open("server.db", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (file < 0)
        return;
    write(file, &server->users_by_name->size, sizeof(int));
    for (int i = 0; i < server->users_by_name->size; i++)
        write(file, server->users_by_name->elems[i].value, sizeof(user_t));
    write(file, &server->teams->size, sizeof(int));
    for (int i = 0; i < server->teams->size; i++)
        save_team(server->teams->elems[i].value, file);
    write(file, &server->messages->size, sizeof(int));
    for (int i = 0; i < server->messages->size; i++)
        save_message_list(server->messages->elems[i].key,
                            server->messages->elems[i].value, file);
}
