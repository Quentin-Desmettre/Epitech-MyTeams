/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** errors
*/

#include "server.h"

void send_error(user_t *client, uint8_t code, const char *msg)
{
    uint16_t msg_len = msg ? strlen(msg) : 0;
    size_t total_size = 11 + msg_len;
    void *data = malloc(total_size);

    memcpy(data, &total_size, 8);
    memcpy(data + 8, &code, 1);
    memcpy(data + 9, &msg_len, 2);
    if (msg)
        memcpy(data + 11, msg, msg_len);
    write(client->fd, data, total_size);
}
