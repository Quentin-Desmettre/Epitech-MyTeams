/*
** EPITECH PROJECT, 2023
** EPITECH_MYTEAMS_MY_WRITE_C
** File description:
** my_write.c
*/

#include <unistd.h>
#include <stdio.h>

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
