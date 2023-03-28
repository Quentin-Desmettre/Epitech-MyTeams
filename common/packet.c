/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** packet
*/

#include "myteams.h"

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
