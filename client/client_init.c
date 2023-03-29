/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** client_init
*/

#include "client.h"

bool connect_client(client_t *client, char *server_ip, int port)
{
    int sockfd;
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        fprintf(stderr, "socket creation failed...\n");
        return false;
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(server_ip);
    servaddr.sin_port = htons(port);

    if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0) {
        fprintf(stderr, "connection with the server failed...\n");
        return false;
    }
    client->socketFd = sockfd;
    return true;
}

int client_get_port(char *port_str)
{
    char *endptr = NULL;
    int port;

    port = strtol(port_str, &endptr, 10);
    if (port <= 0 || port > 65535 ||
        !(port_str[0] != '\0' && endptr && *endptr == '\0')) {
        fprintf(stderr, "Invalid port number.\n");
        return -1;
    }
    return port;
}

client_t *client_init(char *server_ip, char *server_port)
{
    client_t *client = calloc(sizeof(client_t), 1);
    int port = client_get_port(server_port);

    if (port < 0 || !connect_client(client, server_ip, port))
        return NULL;
    return client;
}
