/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** errors
*/

#include "server.h"

void send_error(client_t *client, uint8_t code, const char *msg)
{
    send_packet(create_packet(code, (const void *[]){msg}, 1), client->fd);
}
