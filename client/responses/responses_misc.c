/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** responses_misc
*/

#include "client.h"

void client_receiver_already_exist(UNUSED void *buffer)
{
	client_error_already_exist();
}

void client_receiver_unauthorized(UNUSED void *buffer)
{
	client_error_unauthorized();
}

void client_receiver_user_subscribed(void *buffer)
{
	char *uuid;
	char *team_uuid;

	read_packet(buffer, "ss", &uuid, &team_uuid);
	client_print_subscribed(uuid, team_uuid);
}

void client_receiver_user_unsubscribed(void *buffer)
{
	char *uuid;
	char *team_uuid;

	read_packet(buffer, "ss", &uuid, &team_uuid);
	client_print_unsubscribed(uuid, team_uuid);
}
