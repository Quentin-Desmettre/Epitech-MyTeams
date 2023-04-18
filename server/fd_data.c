/*
** EPITECH PROJECT, 2022
** B-NWP-400-LIL-4-1-myftp-quentin.desmettre
** File description:
** fd_data.c
*/

#include "server.h"

void disconnect_client(server_t *server, int fd)
{
    client_t *client = map_get(server->clients_by_fd, MCAST fd);

    if (client->logged_in)
        logout_handler(server, client, NULL);
    remove_fd_from_array(&server->client_fds, &server->nb_client, fd);
    update_list(fd);
    map_remove(server->clients_by_fd, MCAST fd);
    shutdown(fd, SHUT_RDWR);
}

void clear_client_buffer(client_t *client)
{
    size_t packet_size = *(size_t *)client->buffer;

    if (client->buf_size > packet_size) {
        client->buf_size -= packet_size;
        memmove(client->buffer, client->buffer + packet_size, client->buf_size);
        client->buffer = realloc(client->buffer, client->buf_size);
    } else if (client->buf_size == packet_size) {
        client->buf_size = 0;
        free(client->buffer);
        client->buffer = NULL;
    }
}

void fd_data_init(server_t *server)
{
    fd_data_t data = {0};
    int max_fd = server->fd;
    list_t *packets = *packet_list();
    packet_t *packet;

    FD_ZERO(&data.read_set);
    FD_ZERO(&data.write_set);
    FD_SET(server->fd, &data.read_set);
    for (int i = 0; i < server->nb_client; i++) {
        FD_SET(server->client_fds[i], &data.read_set);
        max_fd = MAX(max_fd, server->client_fds[i]);
    }
    if (packets) {
        do {
            packet = packets->data;
            FD_SET(packet->dest_fd, &data.write_set);
            packets = packets->next;
        } while (packets != *packet_list());
    }
    server->fd_data = data;
}

void remove_fd_from_array(int **array, int *len, int fd)
{
    int fd_index = 0;

    for (; fd_index < (*len) && (*array)[fd_index] != fd; fd_index++);
    if (fd_index == (*len))
        return;
    for (int i = fd_index; i < (*len) - 1; i++)
        (*array)[i] = (*array)[i + 1];
    (*len)--;
    *array = realloc(*array, sizeof(int) * (*len));
}

int get_first_input_available(fd_data_t *data,
                                server_t *server, bool *is_write)
{
    int nb_fd = server->nb_client;
    list_t *packets = *packet_list();
    packet_t *packet;
    *is_write = false;
    if (FD_ISSET(server->fd, &data->read_set))
        return server->fd;
    for (int i = 0; i < nb_fd; i++)
        if (FD_ISSET(server->client_fds[i], &data->read_set))
            return server->client_fds[i];
    if (packets) {
        do {
            packet = packets->data;
            if (FD_ISSET(packet->dest_fd, &data->write_set)) {
                *is_write = true;
                return packet->dest_fd;
            }
            packets = packets->next;
        } while (packets != *packet_list());
    }
    return -1;
}
