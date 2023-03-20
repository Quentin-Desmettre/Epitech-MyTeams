/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** myteams
*/

#ifndef EPITECH_MYTEAMS_MYTEAMS_H
    #define EPITECH_MYTEAMS_MYTEAMS_H
    #include <time.h>
    #include <stdbool.h>
    #include <stdio.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <netinet/ip.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <errno.h>
    #include <sys/select.h>
    #include <stdlib.h>
    #include <string.h>
    #include <pwd.h>
    #include <sys/ioctl.h>
    #include <linux/limits.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include "linked_list.h"
    #include "map.h"
    #define UNUSED __attribute__((unused))
    #define MAX_CLIENTS 100
    #define MAX_NAME_LENGTH 32
    #define MAX_DESCRIPTION_LENGTH 255
    #define MAX_BODY_LENGTH 512
    #define UUID_LENGTH 16
    #define MAX(x, y) ((x) > (y) ? (x) : (y))

typedef struct team {
    char uuid[UUID_LENGTH];
    char name[MAX_NAME_LENGTH + 1];
    char description[MAX_DESCRIPTION_LENGTH + 1];
    map_t *channels; // <== Maps uuid_channel -> channel_t
    list_t *users;
} team_t;

typedef struct channel {
    char uuid[UUID_LENGTH];
    char name[MAX_NAME_LENGTH + 1];
    char description[MAX_DESCRIPTION_LENGTH + 1];
    map_t *threads; // <== Maps uuid_thread -> thread_t
} channel_t;

typedef struct thread {
    char uuid[UUID_LENGTH];
    char title[MAX_NAME_LENGTH + 1];
    char message[MAX_BODY_LENGTH + 1];
    time_t timestamp;
    list_t *replies;
} thread_t;

typedef struct thread_message {
    char uuid_sender[UUID_LENGTH];
    char uuid_receiver[UUID_LENGTH];
    time_t timestamp;
    char content[MAX_BODY_LENGTH + 1];
} thread_message_t;

typedef struct user_context {
    team_t *team;
    channel_t *channel;
    thread_t *thread;
} user_context_t;

typedef struct user {
    int fd;
    bool logged_in;

    char uuid[UUID_LENGTH];
    char name[MAX_NAME_LENGTH + 1];
    user_context_t context;

    void *buffer;
    size_t buf_size;
} user_t;

typedef struct message {
    char uuid_sender[UUID_LENGTH];
    char uuid_receiver[UUID_LENGTH];
    time_t timestamp;
    char content[MAX_BODY_LENGTH + 1];
} user_message_t;

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

    map_t *users;      // <== Maps fd -> user_t
    map_t *messages;   // <== Maps "uuid_user1-uuid_user2" -> list of messages
    int *client_fds;
    int nb_client;
} server_t;

enum ErrorCode {
    Success,
    UnknownTeam,
    UnknownChannel,
    UnknownThread,
    UnknownUser,
    Unauthorized,
    AlreadyExist,
    UnknownCommand
};


// Commands
enum COMMANDS {
    HELP = 0,
    LOGIN,
    LOGOUT,
    USERS,
    USER,
    SEND,
    MESSAGES,
    SUBSCRIBE,
    SUBSCRIBED,
    UNSUBSCRIBE,
    USE,
    CREATE,
    LIST,
    INFO,
    NB_COMMANDS
};

typedef struct {
    bool requires_login;
    int nb_args;
    void (*handler)(server_t *server, user_t *user, char **args);
} command_handler_t;

static void help_handler(server_t *server, user_t *user, char **args) {}
static void login_handler(server_t *server, user_t *user, char **args) {}
static void logout_handler(server_t *server, user_t *user, char **args) {}
static void users_handler(server_t *server, user_t *user, char **args) {}
static void user_handler(server_t *server, user_t *user, char **args) {}
static void send_handler(server_t *server, user_t *user, char **args) {}
static void messages_handler(server_t *server, user_t *user, char **args) {}
static void subscribe_handler(server_t *server, user_t *user, char **args) {}
static void subscribed_handler(server_t *server, user_t *user, char **args) {}
static void unsubscribe_handler(server_t *server, user_t *user, char **args) {}
static void use_handler(server_t *server, user_t *user, char **args) {}
static void create_handler(server_t *server, user_t *user, char **args) {}
static void list_handler(server_t *server, user_t *user, char **args) {}
static void info_handler(server_t *server, user_t *user, char **args) {}

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
int run_server(server_t *server); // Call create_client, read_client, disconnect_client
//void save_server(server_t *server);
//void restore_server(server_t *server);
void accept_client(server_t *server);


// Client
user_t *create_user(int fd);
void free_user(user_t *user);
void handle_user_input(server_t *server, int fd);

// Teams
static void free_team(team_t *team) {}

// Utility
int uuid_compare(const void *a, const void *b);
int int_compare(const void *a, const void *b);
int bytes_available(int fd);
void free_str_array(char **array);
void append_str_array(char ***array, char *what);

// Responses
void send_error(user_t *client, uint8_t code, const char *message);


// Fd sets
void fd_data_init(server_t *server);
int get_first_input_available(fd_data_t *data, server_t *server);
void remove_fd_from_array(int **array, int *len, int fd);

#endif //EPITECH_MYTEAMS_MYTEAMS_H
