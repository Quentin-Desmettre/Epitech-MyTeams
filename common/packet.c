/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** packet
*/

#include "myteams.h"
#include <stdarg.h>

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

bool read_packet(void *packet, const char *params, ...)
{
    va_list ap;
    uint16_t arg_len;
    char **arg_str;
    int offset = 0;
    if (((uint64_t *)packet)[0] < 13)
        return false;
    va_start(ap, params);
    for (int i = 0; params[i]; i++) {
        if (!fetch_arg_len(packet, &arg_len, offset, params[i]))
            return false;
        if (params[i] == 's') {
            arg_str = va_arg(ap, char **);
            *arg_str = malloc(arg_len);
            memcpy(*arg_str, packet + 13 + offset, arg_len);
        } if (params[i] == 't')
            memcpy(va_arg(ap, time_t *), packet + 13 + offset, arg_len);
		if (params[i] == 'i') {
			memcpy(va_arg(ap, int *), packet + 13 + offset, 4);
		}
        offset += 2 + arg_len;
    }
    va_end(ap);
    return true;
}

list_t *read_packet_list(void *packet, char const *packet_content)
{
	list_t *packets = NULL;
	void *tmp_packet;
	uint16_t nb_args = ((uint16_t *)(packet + 9))[0];
	uint16_t nb_packets;
	uint16_t arg_len;
	int offset = 0;

	if (nb_args % strlen(packet_content) != 0)
		return NULL;
	nb_packets = nb_args / strlen(packet_content);
	for (int i = 0; i < nb_packets; i++) {
		tmp_packet = create_packet(0, NULL, NULL, 0);
		for (int j = 0; j < strlen(packet_content); j++) {
			if (!fetch_arg_len(packet, &arg_len, offset, packet_content[j])) {
				return NULL;
			}
			append_arg_to_packet(&tmp_packet, packet + 13 + offset, arg_len);
			offset += 2 + arg_len;
		}
		append_node(&packets, tmp_packet);
	}
	return packets;
}
