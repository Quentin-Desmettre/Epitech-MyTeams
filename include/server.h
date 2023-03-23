/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** server
*/

#ifndef EPITECH_MYTEAMS_SERVER_H
    #define EPITECH_MYTEAMS_SERVER_H
    #include "myteams.h"
    #include "logging_server.h"

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
    void (*handler)(server_t *server, client_t *user, char **args);
} command_handler_t;

void help_handler(server_t *server, client_t *user, char **args);
void login_handler(server_t *server, client_t *user, char **args);
void logout_handler(server_t *server, client_t *user, char **args);
void users_handler(server_t *server, client_t *user, char **args);
void user_handler(server_t *server, client_t *user, char **args);
void send_handler(server_t *server, client_t *user, char **args);
void messages_handler(server_t *server, client_t *user, char **args);
void subscribe_handler(server_t *server, client_t *user, char **args);
void subscribed_handler(server_t *server, client_t *user, char **args);
void unsubscribe_handler(server_t *server, client_t *user, char **args);
void use_handler(server_t *server, client_t *user, char **args);
void create_handler(server_t *server, client_t *user, char **args);
void list_handler(server_t *server, client_t *user, char **args);
void info_handler(server_t *server, client_t *user, char **args);

UNUSED static const command_handler_t COMMANDS[] = {
{false, 0, &help_handler}, // HELP
{false, 2, &login_handler}, // LOGIN
{true, 0, &logout_handler}, // LOGOUT
{true, 0, &users_handler}, // USERS
{true, 1, &user_handler}, // USER
{true, 2, &send_handler}, // SEND
{true, 0, &messages_handler}, // MESSAGES
{true, 1, &subscribe_handler}, // SUBSCRIBE
{true, 0, &subscribed_handler}, // SUBSCRIBED
{true, 1, &unsubscribe_handler}, // UNSUBSCRIBE
{true, 1, &use_handler}, // USE
{true, 3, &create_handler}, // CREATE
{true, 0, &list_handler}, // LIST
{true, 1, &info_handler} // INFO
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

#endif //EPITECH_MYTEAMS_SERVER_H
