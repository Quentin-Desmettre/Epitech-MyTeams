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
    #include <uuid/uuid.h>
    #define UNUSED __attribute__((unused))
    #define MAX_CLIENTS 100
    #define MAX_NAME_LENGTH 32
    #define MAX_DESCRIPTION_LENGTH 255
    #define MAX_BODY_LENGTH 512
    #define UUID_LENGTH 16
    #define MAX(x, y) ((x) > (y) ? (x) : (y))

typedef struct team {
    char uuid[UUID_LENGTH + 1];
    char name[MAX_NAME_LENGTH + 1];
    char description[MAX_DESCRIPTION_LENGTH + 1];
    map_t *channels; // <== Maps uuid_channel -> channel_t
    list_t *users; // <== List of uuid_user
} team_t;

typedef struct channel {
    char uuid[UUID_LENGTH + 1];
    char name[MAX_NAME_LENGTH + 1];
    char description[MAX_DESCRIPTION_LENGTH + 1];
    map_t *threads; // <== Maps uuid_thread -> thread_t
} channel_t;

typedef struct thread {
    char uuid[UUID_LENGTH + 1];
    char uuid_creator[UUID_LENGTH + 1];
    char title[MAX_NAME_LENGTH + 1];
    char message[MAX_BODY_LENGTH + 1];
    time_t timestamp;
    list_t *replies;
} thread_t;

typedef struct thread_message {
    char uuid_sender[UUID_LENGTH + 1];
    char content[MAX_BODY_LENGTH + 1];
    time_t timestamp;
} thread_message_t;

typedef struct user_context {
    team_t *team;
    channel_t *channel;
    thread_t *thread;
} user_context_t;

typedef struct message {
    char uuid_sender[UUID_LENGTH + 1];
    char uuid_receiver[UUID_LENGTH + 1];
    time_t timestamp;
    char content[MAX_BODY_LENGTH + 1];
} user_message_t;

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

static const int NB_ARGS_FOR_REQUEST[] = {
    0, // Help
    1, // Login
    0, // Logout
    0, // Users
    1, // User
    2, // Send
    1, // Messages
    1, // Subscribe
    1, // Subscribed
    1, // Unsubscribe
    3, // Use
    2, // Create
    0, // List
    0  // Info
};

enum responses {
    EV_HELP = 0,
    EV_LOGGED_IN,
    EV_LOGGED_OUT,
    EV_MESSAGE_RECEIVED,
    G_REPLY_CREATED,
    U_REPLY_CREATED,
    G_TEAM_CREATED,
    U_TEAM_CREATED,
    G_CHANNEL_CREATED,
    U_CHANNEL_CREATED,
    G_THREAD_CREATED,
    U_THREAD_CREATED,
    EV_LIST_USERS,
    EV_LIST_TEAMS,
    EV_LIST_CHANNELS,
    EV_LIST_THREADS,
    EV_LIST_REPLIES,
    EV_LIST_MESSAGES,
    UNKNOWN_TEAM,
    UNKNOWN_CHANNEL,
    UNKNOWN_THREAD,
    UNKNOWN_USER,
    UNAUTHORIZED,
    UNKNOWN_COMMAND,
    ALREADY_EXIST,
    EV_USER_INFO,
    EV_TEAM_INFO,
    EV_CHANNEL_INFO,
    EV_THREAD_INFO,
    USER_SUBSCRIBED,
    USER_UNSUBSCRIBED,
};

static const int NB_ARGS_FOR_RESPONSE[] = {
    1, // Help
    2, // Login
    2, // Logout

    2, // Message received

    4, // Global: thread reply created
    4, // User: thread reply created

    3, // Global: team created
    3, // User: team created

    3, // Global: channel created
    3, // User: channel created

    5, // Global: thread created
    5, // User: thread created

    -1, // List users
    -1, // List teams
    -1, // List channels
    -1, // List threads
    -1, // List replies
    -1, // List messages

    0, // Unknown team
    0, // Unknown channel
    0, // Unknown thread
    0, // Unknown user
    0, // Unauthorized
    0, // Unknown command
    0, // Already exist

    3, // User info
    3, // Team info
    3, // Channel info
    3, // Thread info

    2, // User subscribed
    2, // User unsubscribed
};

// Utility
int int_compare(const void *a, const void *b);
int bytes_available(int fd);
void free_str_array(char **array);
void append_str_array(char ***array, char *what);
void *memdup(void *src, size_t size);
void generate_uuid(char *uuid);
char **strarr(char *str, char *delim);

// Packet
bool is_error(enum responses code);
void append_arg_to_packet(void **packet, const void *arg, uint16_t arg_len);
void *create_packet(enum responses code, const void **args,
        const int args_lens[], int nb_args);
void send_packet(void *packet, int fd, bool to_free);
void safe_write(int fd, void *data, size_t len);

#endif //EPITECH_MYTEAMS_MYTEAMS_H
