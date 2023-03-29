/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** responses_list
*/

#include "client.h"

void client_receiver_list_threads(client_t *client)
{
	list_t *packets = read_packet_list(client->buffer, "sstss");
	list_t *it = packets;
	char *uuid;
	char *uuid_creator;
	time_t timestamp;
	char *title;
	char *message;

	if (!packets)
		return;
	do {
		read_packet(it->data, "sstss", &uuid, &uuid_creator,
			&timestamp, &title, &message);
		client_print_thread(uuid, uuid_creator, timestamp, title, message);
		it = it->next;
	} while ((it != packets));
}

void client_receiver_list_replies(client_t *client)
{

}

void client_receiver_list_messages(client_t *client)
{

}

void client_receiver_list_users(client_t *client)
{
	list_t *packets = read_packet_list(client->buffer, "ssi");
	list_t *it = packets;
	char *uuid;
	char *name;
	uint64_t status;

	printf("Packets: %p\n", packets);
	if (!packets)
		return;
	printf("Users:\n");
	do {
		read_packet(packets->data, "ssi", &uuid, &name, &status);
		client_print_users(&uuid, &name, status);
		it = it->next;
	} while ((it != packets));
}

void client_receiver_list_teams(client_t *client)
{
	list_t *packets = read_packet_list(client->buffer, "sss");
	list_t *it = packets;
	char *uuid;
	char *name;
	char *description;

	if (!packets)
		return;
	do {
		read_packet(it->data, "sss", &uuid, &name, &description);
		client_print_team(uuid, name, description);
		it = it->next;
	} while ((it != packets));
}

void client_receiver_list_channels(client_t *client)
{
	list_t *packets = read_packet_list(client->buffer, "sss");
	list_t *it = packets;
	char *uuid;
	char *name;
	char *description;

	if (!packets)
		return;
	do {
		read_packet(it->data, "sss", &uuid, &name, &description);
		client_print_channel(uuid, name, description);
		it = it->next;
	} while ((it != packets));
}