/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** server
*/

#ifndef EPITECH_MYTEAMS_SERVER_H
    #define EPITECH_MYTEAMS_SERVER_H
    #include "myteams.h"

    #ifndef NO_INCLUDE_TEAMS
        #include "logging_server.h"
    #endif

// Client
typedef struct user {
    char uuid[UUID_LENGTH];
    char name[MAX_NAME_LENGTH + 1];
} user_t;

typedef struct client {
    int fd;
    bool logged_in;

    user_context_t context;
    user_t *user;

    void *buffer;
    size_t buf_size;
} client_t;

typedef struct {
    int max_fd;
    fd_set read_set;
    fd_set write_set;
    fd_set except_set;
} fd_data_t;

typedef struct server {
    int fd;
    bool run;
    fd_data_t fd_data;

    map_t *teams;      // <== Maps uuid_team -> team_t

    map_t *clients_by_fd;        // <== Maps fd -> client_t
    map_t *clients_by_uuid;      // <== Maps uuid -> client_t
    map_t *users_by_uuid;        // <== Maps uuid_user -> user_t
    map_t *users_by_name;        // <== Maps name_user -> user_t
    map_t *messages;   // <== Maps "uuid_user1-uuid_user2" -> list of messages
    int *client_fds;
    int nb_client;
} server_t;

typedef struct {
    bool requires_login;
    int nb_args;
    void (*handler)(server_t *server, client_t *client, char **args);
} command_handler_t;

void help_handler(server_t *server, client_t *client, char **args);
void login_handler(server_t *server, client_t *client, char **args);
void logout_handler(server_t *server, client_t *client, char **args);
void users_handler(server_t *server, client_t *client, char **args);
void user_handler(server_t *server, client_t *client, char **args);
void send_handler(server_t *server, client_t *client, char **args);
void messages_handler(server_t *server, client_t *client, char **args);
void subscribe_handler(server_t *server, client_t *client, char **args);
void subscribed_handler(server_t *server, client_t *client, char **args);
void unsubscribe_handler(server_t *server, client_t *client, char **args);
void use_handler(server_t *server, client_t *client, char **args);
void create_handler(server_t *server, client_t *client, char **args);
void list_handler(server_t *server, client_t *client, char **args);
void info_handler(server_t *server, client_t *client, char **args);

UNUSED static const command_handler_t COMMANDS[] = {
        {false, 0, &help_handler}, // HELP
        {false, 1, &login_handler}, // LOGIN
        {true, 0, &logout_handler}, // LOGOUT
        {true, 0, &users_handler}, // USERS
        {true, 1, &user_handler}, // USER
        {true, 2, &send_handler}, // SEND
        {true, 1, &messages_handler}, // MESSAGES
        {true, 1, &subscribe_handler}, // SUBSCRIBE
        {true, 1, &subscribed_handler}, // SUBSCRIBED
        {true, 1, &unsubscribe_handler}, // UNSUBSCRIBE
        {true, 3, &use_handler}, // USE
        {true, 2, &create_handler}, // CREATE
        {true, 0, &list_handler}, // LIST
        {true, 0, &info_handler} // INFO
};

// Server
int get_port(int ac, char **av);
server_t *init_server(int port); // Creates a socket, bind, listen
void destroy_server(server_t *server);
int run_server(server_t *server);
void save_server(server_t *server);
void restore_server(server_t *server);
void accept_client(server_t *server);

// Client
void handle_client_input(server_t *server, int fd);
void free_client(client_t *client);
void disconnect_client(server_t *server, int fd);
void clear_client_buffer(client_t *client);
char *get_uuid_pair(const char *uuid_1, const char *uuid_2);

// Teams
void free_team(team_t *team);
void free_message_list(list_t *messages);
void free_thread(void *th);
void free_channel(void *ch);

// Responses
void send_error(client_t *client, uint8_t code, const char *message);

// Fd sets
void fd_data_init(server_t *server);
int get_first_input_available(fd_data_t *data, server_t *server);
void remove_fd_from_array(int **array, int *len, int fd);

// Utility
bool thread_exists(const char *name, channel_t *channel);
bool channel_exists(const char *name, team_t *team);
bool team_exists(const char *name, server_t *server);
bool is_user_subscribed(client_t *client, team_t *team);

// Create notifications
void notify_team_creation(team_t *t, server_t *server, client_t *client);
void notify_channel_creation(channel_t *ch,
    server_t *server, client_t *client);
void notify_thread_creation(thread_t *th, server_t *server, client_t *client);
void notify_thread_message_creation(thread_message_t *m,
    server_t *server, client_t *client);
#endif //EPITECH_MYTEAMS_SERVER_H
