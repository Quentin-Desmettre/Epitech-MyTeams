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
    for (int i = 1; i < 3; i++) {
		if (args[i] != NULL)
            append_arg_to_packet(&packet, args[i], strlen(args[i]) + 1);
		else
			append_arg_to_packet(&packet, "", 1);
	}
    send_packet(packet, client->socketFd, true);
}

void client_create(client_t *client, char **args)
{
    void *packet = create_packet(CREATE, NULL, NULL, 0);
    for (int i = 1; args[i]; i++)
        append_arg_to_packet(&packet, args[i], strlen(args[i]) + 1);
    send_packet(packet, client->socketFd, true);
}

void client_exit(client_t *client, UNUSED char **args)
{
    void *packet = create_packet(NB_COMMANDS, NULL, NULL, 0);
    send_packet(packet, client->socketFd, true);
}
