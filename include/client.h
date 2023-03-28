/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** client
*/

#ifndef EPITECH_MYTEAMS_CLIENT_H
    #define EPITECH_MYTEAMS_CLIENT_H

    #include "myteams.h"

typedef struct client_context {
    char team_uuid[UUID_LENGTH + 1];
    char channel_uuid[UUID_LENGTH + 1];
    char thread_uuid[UUID_LENGTH + 1];
} client_context_t;

typedef struct client {
    int socketFd;

    char client_uuid[UUID_LENGTH + 1];
    char client_name[MAX_NAME_LENGTH + 1];

    client_context_t context;

    char *input_buffer;
    char **input_args;
    size_t input_buffer_size;

} client_t;

client_t *client_init(char *server_ip, char *server_port);
void client_run(client_t *client);
void client_input(client_t *client);


#endif //EPITECH_MYTEAMS_CLIENT_H
