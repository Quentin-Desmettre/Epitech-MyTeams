/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** create_notify
*/

#include "server.h"

void notify_team_creation(team_t *t, server_t *server, client_t *client)
{
    void *packet = create_packet(G_TEAM_CREATED, NULL, NULL, 0);

    append_arg_to_packet(&packet, t->uuid, sizeof(t->uuid));
    append_arg_to_packet(&packet, t->name, strlen(t->name) + 1);
    append_arg_to_packet(&packet, t->description, strlen(t->description) + 1);
    for (int i = 0; i < server->clients_by_uuid->size; i++)
        send_packet(packet, ((client_t *)(server->clients_by_uuid->elems[i]
        .value))->fd, false);
    ((uint8_t *)packet)[8] = U_TEAM_CREATED;
    send_packet(packet, client->fd, true);
}

static void notify_team(void *packet, team_t *team, server_t *server)
{
    list_t *users = team->users;
    client_t *c;

    if (!users)
        return;
    do {
        c = map_get(server->clients_by_uuid, users->data);
        if (c)
            send_packet(packet, c->fd, false);
        users = users->next;
    } while (users != team->users);
}

void notify_channel_creation(channel_t *ch, server_t *server, client_t *client)
{
    void *packet = create_packet(G_CHANNEL_CREATED, NULL, NULL, 0);
    team_t *t = map_get(server->teams, client->context.team);

    append_arg_to_packet(&packet, ch->uuid, sizeof(ch->uuid));
    append_arg_to_packet(&packet, ch->name, strlen(ch->name) + 1);
    append_arg_to_packet(&packet,
        ch->description, strlen(ch->description) + 1);
    notify_team(packet, t, server);
    ((uint8_t *)packet)[8] = U_CHANNEL_CREATED;
    send_packet(packet, client->fd, true);
}

void notify_thread_creation(thread_t *th, server_t *server, client_t *client)
{
    void *packet = create_packet(G_THREAD_CREATED, NULL, NULL, 0);
    team_t *t = map_get(server->teams, client->context.team);

    append_arg_to_packet(&packet, th->uuid, sizeof(th->uuid));
    append_arg_to_packet(&packet, client->user->uuid, sizeof(client->user->uuid));
    append_arg_to_packet(&packet, &th->timestamp, sizeof(time_t));
    append_arg_to_packet(&packet, th->title, strlen(th->title) + 1);
    append_arg_to_packet(&packet, th->message, strlen(th->message) + 1);
    notify_team(packet, t, server);
    ((uint8_t *)packet)[8] = U_THREAD_CREATED;
    send_packet(packet, client->fd, true);
}

void notify_thread_message_creation(thread_message_t *m,
                                    server_t *s, client_t *c)
{
    void *p = create_packet(U_REPLY_CREATED, NULL, NULL, 0);
    team_t *t = map_get(s->teams, c->context.team);

    append_arg_to_packet(&p, c->context.thread, sizeof(c->context.thread));
    append_arg_to_packet(&p, c->user->uuid, sizeof(c->user->uuid));
    append_arg_to_packet(&p, &m->timestamp, sizeof(time_t));
    append_arg_to_packet(&p, m->content, strlen(m->content) + 1);
    send_packet(p, c->fd, true);
    p = create_packet(G_REPLY_CREATED, NULL, NULL, 0);
    append_arg_to_packet(&p, c->context.team, sizeof(c->context.team));
    append_arg_to_packet(&p, c->context.thread, sizeof(c->context.thread));
    append_arg_to_packet(&p, c->user->uuid, sizeof(c->user->uuid));
    append_arg_to_packet(&p, m->content, strlen(m->content) + 1);
    notify_team(p, t, s);
}
