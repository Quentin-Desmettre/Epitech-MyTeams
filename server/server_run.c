/*
** EPITECH PROJECT, 2022
** Epitech-Template
** File description:
** main.c
*/

#include "server.h"

void accept_client(server_t *server)
{
    int fd = accept(server->fd, NULL, NULL);
    int nfd = server->nb_client;
    client_t *client;

    if (fd == -1)
        return;
    server->client_fds = realloc(server->client_fds, sizeof(int) * (nfd + 1));
    server->client_fds[nfd] = fd;
    server->nb_client++;
    client = calloc(sizeof(client_t), 1);
    client->fd = fd;
    map_add(server->clients_by_fd, MCAST fd, client);
}

char **get_request_arguments(void *request, size_t buf_size, int nb_args)
{
    char **args = NULL;
    int offset = 0;
    char *arg;
    uint16_t arg_len;

    for (int i = 0; i < nb_args; i++) {
        arg_len = *(uint16_t *)(request + 11 + offset);
        if (arg_len > buf_size - 13 - offset) {
            free(args);
            return NULL;
        }
        arg = malloc(arg_len + 1);
        memcpy(arg, request + 13 + offset, arg_len);
        arg[arg_len] = 0;
        append_str_array(&args, arg);
        offset += arg_len;
    }
    return args;
}

void handle_request(server_t *server, client_t *client)
{
    uint8_t cmd_id = ((uint8_t *)client->buffer)[8];
    char **args = NULL;
    const command_handler_t *handler;

    if (cmd_id >= NB_COMMANDS)
        return clear_client_buffer(client),
        send_error(client, UNKNOWN_COMMAND, "");
    handler = &COMMANDS[cmd_id];
    args = get_request_arguments(client->buffer,
                                client->buf_size, handler->nb_args);
    clear_client_buffer(client);
    if (!args)
        return send_error(client, UNKNOWN_COMMAND, "");
    if (handler->requires_login && !client->logged_in)
        return send_error(client, UNAUTHORIZED, "");
    handler->handler(server, client, args);
    free_str_array(args);
}

void handle_client_input(server_t *server, int fd)
{
    int bytes = bytes_available(fd);
    client_t *client;
    char *tmp_buf;

    if (bytes < 0)
        return;
    if (bytes == 0)
        return disconnect_client(server, fd);
    client = map_get(server->clients_by_fd, MCAST fd);
    tmp_buf = malloc(bytes);
    if (read(fd, tmp_buf, bytes) != bytes)
        return free(tmp_buf);
    client->buffer = realloc(client->buffer, client->buf_size + bytes);
    memcpy(client->buffer + client->buf_size, tmp_buf, bytes);
    client->buf_size += bytes;
    free(tmp_buf);
    if (client->buf_size >= 8 && client->buf_size >= *(size_t *)client->buffer)
        handle_request(server, client);
}

int run_server(server_t *server)
{
    int fd;

    while (server->run) {
        fd_data_init(server);
        if (select(server->fd_data.max_fd + 1, &server->fd_data.read_set,
            NULL, NULL, NULL) == -1)
            continue;
        fd = get_first_input_available(&server->fd_data, server);
        if (fd == server->fd)
            accept_client(server);
        else {
            handle_client_input(server, fd);
            save_server(server);
        }
    }
    return 0;
}
