/*
** EPITECH PROJECT, 2023
** EPITECH_MYTEAMS_CLIENT_HANDLE_SERVER_C
** File description:
** client_handle_server.c
*/

#include "client.h"

static void handle_action(client_t *client)
{
    uint8_t cmd_id = ((uint8_t *)client->buffer)[8];
    const command_receiver_t *handler = NULL;

    if (cmd_id >= NB_RESPONSES) {
        printf("Invalid command id: %d\n", cmd_id);
        return;
    }

    handler = &RESPONSES[cmd_id];
    handler->func(client);
}

static void handle_server_return(client_t *client)
{
    size_t currPacket = *(size_t *)client->buffer;
    size_t tmp;

    while (currPacket <= client->buf_size) {
        handle_action(client);
        memmove(client->buffer,
        client->buffer + currPacket, client->buf_size - currPacket);
        tmp = *(size_t *)(client->buffer + currPacket);
        if (tmp == 0)
            break;
        currPacket += tmp;
    }
    free(client->buffer);
    client->buffer = NULL;
    client->buf_size = 0;
}

int client_read(client_t *client)
{
    int bytes = bytes_available(client->socketFd);
    char *tmp_buf;

    if (bytes < 0)
        return 0;
    if (bytes == 0)
        return -1;
    tmp_buf = calloc(1, bytes);
    if (read(client->socketFd, tmp_buf, bytes) != bytes)
        return free(tmp_buf), 0;
    client->buffer = realloc(client->buffer, client->buf_size + bytes);
    memcpy(client->buffer + client->buf_size, tmp_buf, bytes);
    client->buf_size += bytes;
    free(tmp_buf);
    if (client->buf_size >= 8 && client->buf_size >= *(size_t *)client->buffer)
        handle_server_return(client);
    return 0;
}
