/*
** EPITECH PROJECT, 2023
** EPITECH_MYTEAMS_JAI_PAS_TROUVER_DE_NOM_C
** File description:
** jai_pas_trouver_de_nom.c
*/

#include "client.h"

void client_use(client_t *client, char **args)
{
    void *packet = create_packet(USE, NULL, NULL, 0);
    append_arg_to_packet(&packet, args[1],
        strlen(args[1]) + 1);
    send_packet(packet, client->socketFd, true);
}

void client_create(client_t *client, char **args)
{
    void *packet = create_packet(CREATE, NULL, NULL, 0);
    append_arg_to_packet(&packet, args[1],
        strlen(args[1]) + 1);
    append_arg_to_packet(&packet, args[2],
        strlen(args[2]) + 1);
    send_packet(packet, client->socketFd, true);
}

void client_exit(client_t *client, UNUSED char **args)
{
    void *packet = create_packet(NB_COMMANDS, NULL, NULL, 0);
    send_packet(packet, client->socketFd, true);
}
