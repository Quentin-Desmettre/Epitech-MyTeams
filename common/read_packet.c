/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** read_packet
*/

#include <stdarg.h>
#include "myteams.h"

static bool fetch_arg_len(void *packet,
                        uint16_t *arg_len, int offset, char param)
{
    const uint64_t packet_size = ((uint64_t *)packet)[0];

    if (11 + offset + 2 > packet_size)
        return false;
    *arg_len = *(uint16_t *)(packet + 11 + offset);
    if (11 + offset + 2 + *arg_len > packet_size)
        return false;
    if (param == 't' && *arg_len != sizeof(time_t))
        return false;
    if (param == 'i' && *arg_len != sizeof(int))
        return false;
    return true;
}

static bool read_arg(void *packet, int *offset, char param, va_list *ap)
{
    uint16_t arg_len;
    char **arg_str;

    if (!fetch_arg_len(packet, &arg_len, *offset, param))
        return false;
    if (param == 's') {
        arg_str = va_arg(*ap, char **);
        *arg_str = calloc(1, arg_len);
        memcpy(*arg_str, packet + 13 + *offset, arg_len);
    } if (param == 't')
        memcpy(va_arg(*ap, time_t *), packet + 13 + *offset, arg_len);
    if (param == 'i')
        memcpy(va_arg(*ap, int *), packet + 13 + *offset, 4);
    *offset += 2 + arg_len;
    return true;
}

bool read_packet(void *packet, const char *params, ...)
{
    va_list ap;
    int offset = 0;

    if (((uint64_t *)packet)[0] < 13)
        return false;
    va_start(ap, params);
    for (int i = 0; params[i]; i++) {
        if (!read_arg(packet, &offset, params[i], &ap))
            return false;
    }
    va_end(ap);
    return true;
}

static void *fetch_current_packet(void *packet,
                            char const *packet_content, int *offset)
{
    void *tmp_packet = create_packet(0, NULL, NULL, 0);
    uint16_t arg_len;

    for (int j = 0; j < strlen(packet_content); j++) {
        if (!fetch_arg_len(packet, &arg_len, *offset, packet_content[j]))
            return NULL;
        append_arg_to_packet(&tmp_packet, packet + 13 + *offset, arg_len);
        *offset += 2 + arg_len;
    }
    return tmp_packet;
}

list_t *read_packet_list(void *packet, char const *packet_content)
{
    list_t *packets = NULL;
    void *tmp_packet;
    uint16_t nb_args = ((uint16_t *)(packet + 9))[0];
    uint16_t nb_packets;
    int offset = 0;

    if (nb_args % strlen(packet_content) != 0)
        return NULL;
    nb_packets = nb_args / strlen(packet_content);
    for (int i = 0; i < nb_packets; i++) {
        tmp_packet = fetch_current_packet(packet, packet_content, &offset);
        append_node(&packets, tmp_packet);
    }
    return packets;
}
