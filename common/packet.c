/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** packet
*/

#include "myteams.h"
#include <stdarg.h>

bool is_error(enum responses code)
{
    return code == UNKNOWN_TEAM || code == UNKNOWN_CHANNEL ||
        code == UNKNOWN_THREAD || code == UNKNOWN_USER ||
        code == UNAUTHORIZED || code == UNKNOWN_COMMAND
        || code == ALREADY_EXIST;
}

void append_arg_to_packet(void **packet, const void *arg, uint16_t arg_len)
{
    uint64_t packet_size = ((uint64_t *)(*packet))[0];

    ((uint16_t *)(*packet + 9))[0] += 1;
    *packet = realloc(*packet, packet_size + 2 + arg_len);
    memcpy(*packet + packet_size, &arg_len, 2);
    memcpy(*packet + packet_size + 2, arg, arg_len);
    ((uint64_t *)(*packet))[0] += 2 + arg_len;
}

void *create_packet(enum responses code, const void **args,
        const int args_lens[], int nb_args)
{
    void *packet = calloc(11, 1);

    ((uint64_t *)packet)[0] = 11;
    ((uint8_t *)packet)[8] = code;
    for (int i = 0; i < nb_args; i++)
        append_arg_to_packet(&packet, args[i], args_lens[i]);
    return packet;
}

void send_packet(void *packet, int fd, bool to_free)
{
    safe_write(fd, packet, ((uint64_t *)packet)[0]);
    if (to_free)
        free(packet);
}

/**
 * @brief Read a packet and fill the given arguments
 * @param packet The packet
 * @param params The parameters to read, 's' for string and 't' for time_t.
 * Example: "sst" for 2 strings and 1 time_t, in this order.
 * @param ... The arguments to fill, should be pointers to string (char **) and
 * pointer to time_t (time_t *).
 */
void read_packet(void *packet, const char *params, ...)
{
    va_list ap;
    uint16_t arg_len;
    char **arg_str;
    int offset = 0;

    va_start(ap, params);
    for (int i = 0; params[i]; i++) {
        if (params[i] == 's') {
            arg_len = *(uint16_t *)(packet + 11 + offset);
            arg_str = va_arg(ap, char **);
            *arg_str = malloc(arg_len);
            memcpy(*arg_str, packet + 13 + offset, arg_len);
            offset += 2 + arg_len;
        }
        if (params[i] == 't') {
            *va_arg(ap, time_t *) = *(time_t *)(packet + 13 + offset);
            offset += 2 + sizeof(time_t);
        }
    }
    va_end(ap);
}
