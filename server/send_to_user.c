/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** send_to_user
*/

#include "server.h"

void send_to_client_list(void *packet, list_t *clients, bool free_packet)
{
    list_t * const begin = clients;
    client_t *c;

    if (!clients)
        return;
    do {
        c = clients->data;
        if (c)
            send_packet(packet, c->fd, false);
        clients = clients->next;
    } while (clients != begin);
    if (free_packet)
        free(packet);
}
