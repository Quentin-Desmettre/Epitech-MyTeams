/*
** EPITECH PROJECT, 2023
** EPITECH_MYTEAMS_MY_WRITE_C
** File description:
** my_write.c
*/

#include <unistd.h>
#include "myteams.h"

void safe_write(int fd, void *data, size_t len)
{
    size_t written = 0;
    ssize_t return_value;

    while (written < len) {
        return_value = write(fd, data + written, len - written);
        if (return_value == -1)
            return;
        written += return_value;
    }
}

void update_list(int fd)
{
    list_t *new_list = NULL;
    list_t *list = *packet_list();

    if (!list)
        return;
    do {
        if (((packet_t *)list->data)->dest_fd != fd)
            append_node(&new_list, list->data);
        else if (((packet_t *)list->data)->free_packet)
            free(((packet_t *)list->data)->raw_packet);
        list = list->next;
    } while (list != *packet_list());
    free_list(packet_list(), NULL);
    *packet_list() = new_list;
}

void handle_output(int fd)
{
    list_t *list = *packet_list();
    packet_t *packet;

    if (!list)
        return;
    do {
        packet = list->data;
        if (packet->dest_fd == fd && !packet->is_sent) {
            safe_write(fd, packet->raw_packet,
                        ((uint64_t *)packet->raw_packet)[0]);
            packet->is_sent = true;
        }
        list = list->next;
    } while (list != *packet_list());
    update_list(fd);
}
