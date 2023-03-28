/*
** EPITECH PROJECT, 2022
** Epitech-Template
** File description:
** main.c
*/

#include "server.h"

static void print_usage(void)
{
    printf("USAGE: ./myteams_server port\n\n");
    printf("\tport\tis the port "
    "number on which the server socket listens.\n");
}

int get_port(int ac, char **av)
{
    char *endptr = NULL;
    int port;

    if (ac != 2 || !strcmp(av[1], "-help")) {
        if (ac != 2)
            fprintf(stderr, "Invalid number of arguments.\n");
        print_usage();
        return (-1);
    }
    port = strtol(av[1], &endptr, 10);
    if (port <= 0 || port > 65535 ||
    !(av[1][0] != '\0' && endptr && *endptr == '\0')) {
        fprintf(stderr, "Invalid port number.\n");
        return (-1);
    }
    return port;
}

static bool init_connection(server_t *serv, int port)
{
    struct sockaddr_in saddr = {0};

    serv->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (serv->fd == -1) {
        perror("socket");
        return (false);
    }
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(port);
    saddr.sin_addr.s_addr = INADDR_ANY;
    if (bind(serv->fd, (const struct sockaddr *)&saddr, sizeof(saddr)) == -1) {
        perror("bind");
        return (false);
    }
    if (listen(serv->fd, MAX_CLIENTS) == -1) {
        perror("listen");
        return (false);
    }
    return (true);
}

server_t *init_server(int port)
{
    server_t *serv = calloc(sizeof(server_t), 1);

    if (!init_connection(serv, port)) {
        destroy_server(serv);
        return (NULL);
    }
    serv->clients_by_fd = map_create(int_compare, (free_value_t)free_client);
    serv->clients_by_uuid = map_create((compare_key_t)strcmp, NULL);
    serv->users_by_uuid = map_create((compare_key_t)strcmp, free);
    serv->users_by_name = map_create((compare_key_t)strcmp, NULL);
    serv->teams = map_create((compare_key_t)strcmp, (free_value_t)free_team);
    serv->messages = map_create((compare_key_t)strcmp,
                                (free_value_t)free_message_list);
    serv->run = true;
    restore_server(serv);
    return (serv);
}

void destroy_server(server_t *serv)
{
    if (serv->fd != -1)
        close(serv->fd);
    map_destroy(serv->clients_by_fd);
    map_destroy(serv->clients_by_uuid);
    map_destroy(serv->users_by_uuid);
    map_destroy(serv->users_by_name);
    map_destroy(serv->teams);
    map_destroy(serv->messages);
    free(serv->client_fds);
    free(serv);
}
