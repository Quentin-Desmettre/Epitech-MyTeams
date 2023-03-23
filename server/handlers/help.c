/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** help
*/

#include "server.h"

void help_handler(server_t *server, client_t *client, char **args)
{
    void *packet = create_packet(EV_HELP, (const void *[]){"MyTeams project.\n"
    "Made by the best students of Epitech Lille in 2023.\n"}, 1);

    send_packet(packet, client->fd);
}
