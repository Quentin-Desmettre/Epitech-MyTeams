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

// Client
user_t *create_user(int fd);
void free_user(user_t *user);

// Utility
int uuid_compare(const void *a, const void *b);
int int_compare(const void *a, const void *b);
int bytes_available(int fd);
void free_str_array(char **array);
void append_str_array(char ***array, char *what);

#endif //EPITECH_MYTEAMS_MYTEAMS_H
