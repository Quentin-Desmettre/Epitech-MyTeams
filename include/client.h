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
    int arg_count;
    size_t input_buffer_size;

    void *buffer;
    size_t buf_size;

} client_t;

client_t *client_init(char *server_ip, char *server_port);
void client_run(client_t *client);
void client_input(client_t *client);

/// Command
void client_use(client_t *client, char **args);
void client_create(client_t *client, char **args);
void client_exit(client_t *client, char **args);
void client_send(client_t *client, char **args);
void client_messages(client_t *client, char **args);
void client_subscribe(client_t *client, char **args);
void client_subscribed(client_t *client, char **args);
void client_unsubscribe(client_t *client, char **args);
void client_users(client_t *client, char **args);
void client_user(client_t *client, char **args);
void client_list(client_t *client, char **args);
void client_info(client_t *client, char **args);
void client_help(client_t *client, char **args);
void client_login(client_t *client, char **args);
void client_logout(client_t *client, char **args);

typedef struct command {
    int id;
    char *name;
    int min_args;
    int max_args;
    void (*func)(client_t *, char **);
} command_t;

static const command_t COMMANDS[] = {
        {0, "/login", 2, 2, &client_login},
        {1, "/logout", 1, 1, &client_logout},
        {2, "/users", 1, 1, &client_users},
        {3, "/user", 2, 2, &client_user},
        {4, "/send", 3, 3, &client_send},
        {5, "/messages", 2, 2, &client_messages},
        {6, "/subscribe", 2, 2, &client_subscribe},
        {7, "/subscribed", 1, 1, &client_subscribed},
        {8, "/unsubscribe", 2, 2, &client_unsubscribe},
        {9, "/use", 2, 2, &client_use},
        {10, "/create", 3, 3, &client_create},
        {11, "/list", 1, 1, &client_list},
        {12, "/info", 2, 2, &client_info},
        {13, "/help", 1, 1, &client_help},
        {14, "/exit", 1, 1, &client_exit},
        {15, NULL, 0, 0, NULL}
};

typedef struct command_receiver {
    int id;
    void (*func)(client_t *);
} command_receiver_t;

static const command_receiver_t COMMANDS[] = {
        {0, &client_receiver_help},
        {1, &client_receiver_logged_in},
        {2, &client_receiver_logged_out},
        {3, &client_receiver_message_received},
        {4, &client_receiver_reply_created_g},
        {5, &client_receiver_reply_created_u},
        {6, &client_receiver_team_created_g},
        {7, &client_receiver_team_created_u},
        {8, &client_receiver_channel_created_g},
        {9, &client_receiver_channel_created_u},
        {10, &client_receiver_thread_created_g},
        {11, &client_receiver_thread_created_u},
        {12, &client_receiver_list_users},
        {13, &client_receiver_list_teams},
        {14, &client_receiver_list_channels},
        {15, &client_receiver_list_threads},
        {16, &client_receiver_list_replies},
        {17, &client_receiver_list_messages},
        {18, &client_receiver_unknown_team},
        {19, &client_receiver_unknown_channel},
        {20, &client_receiver_unknown_thread},
        {21, &client_receiver_unknown_user},
        {22, &client_receiver_unauthorized},
        {23, &client_receiver_unknown_command},
        {24, &client_receiver_already_exist},
        {25, &client_receiver_user_info},
        {26, &client_receiver_team_info},
        {27, &client_receiver_channel_info},
        {28, &client_receiver_thread_info},
        {29, &client_receiver_user_subscribed},
        {30, &client_receiver_user_unsubscribed},
        {31, NULL, 0, 0, NULL}
};

#endif //EPITECH_MYTEAMS_CLIENT_H
