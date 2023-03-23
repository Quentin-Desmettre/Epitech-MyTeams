/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** help
*/

#include "server.h"

void help_handler(UNUSED server_t *server,
                    client_t *client, UNUSED char **args)
{
    const char *message = "MyTeams project.\nMade by the best students "
                            "of Epitech Lille in 2023.\n";
    void *packet = create_packet(EV_HELP, (const void *[]){message},
                            (const int []){strlen(message) + 1}, 1);

    send_packet(packet, client->fd);
}
