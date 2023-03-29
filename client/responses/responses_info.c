/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** responses_info
*/

#include "client.h"

void client_receiver_user_info(void *buffer)
{
	char *uuid;
	char *name;
	size_t is_connected;

	read_packet(buffer, "sst", &uuid, &name, &is_connected);
	printf("User [%s] (%s) is %s\n", uuid, name,
        is_connected ? "connected" : "disconnected");
}

void client_receiver_team_info(void *buffer)
{
	char *uuid;
	char *name;
	char *description;

	read_packet(buffer, "sss", &uuid, &name, &description);
	printf("Team [%s] (%s) : %s\n", uuid, name, description);
}

void client_receiver_channel_info(void *buffer)
{
	char *uuid;
	char *name;
	char *description;

	read_packet(buffer, "sss", &uuid, &name, &description);
	printf("Channel [%s] (%s) : %s\n", uuid, name, description);
}

void client_receiver_thread_info(void *buffer)
{
	char *uuid;
	char *name;
	char *description;

	read_packet(buffer, "sss", &uuid, &name, &description);
	printf("Thread [%s] (%s) : %s\n", uuid, name, description);
}