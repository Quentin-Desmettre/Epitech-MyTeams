/*
** EPITECH PROJECT, 2023
** EPITECH_MYTEAMS_THREAD_LIST_C
** File description:
** thread_list.c
*/

#include "client.h"

void client_receiver_thread_created_g(client_t *client)
{
    char *thread_uuid = NULL;
    char *user_uuid = NULL;
    time_t thread_timestamp;
    char *thread_title = NULL;
    char *thread_body = NULL;

    if (!read_packet(client->buffer, "ssts", &thread_uuid, &user_uuid,
        &thread_timestamp, &thread_title, &thread_body))
        return;
    client_event_thread_created(thread_uuid, user_uuid, thread_timestamp,
        thread_title, thread_body);
}

void client_receiver_thread_created_u(client_t *client)
{
    char *thread_uuid = NULL;
    char *user_uuid = NULL;
    time_t thread_timestamp;
    char *thread_title = NULL;
    char *thread_body = NULL;

    if (!read_packet(client->buffer, "ssts", &thread_uuid, &user_uuid,
        &thread_timestamp, &thread_title, &thread_body))
        return;
    client_print_thread_created(thread_uuid, user_uuid, thread_timestamp,
        thread_title, thread_body);

}
