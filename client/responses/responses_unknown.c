/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** responses_unknown
*/

#include "client.h"

void client_receiver_unknown_team(void *buffer)
{
	char *team_uuid;

	read_packet(buffer, "s", &team_uuid);
	client_error_unknown_team(team_uuid);
}

void client_receiver_unknown_channel(void *buffer)
{
	char *channel_uuid;

	read_packet(buffer, "s", &channel_uuid);
	client_error_unknown_channel(channel_uuid);
}

void client_receiver_unknown_thread(void *buffer)
{
	char *thread_uuid;

	read_packet(buffer, "s", &thread_uuid);
	client_error_unknown_thread(thread_uuid);
}

void client_receiver_unknown_user(void *buffer)
{
	char *user_uuid;

	read_packet(buffer, "s", &user_uuid);
	client_error_unknown_user(user_uuid);
}

void client_receiver_unknown_command(void *buffer)
{
	char *command;

	read_packet(buffer, "s", &command);
	printf("%s\n", command);
}