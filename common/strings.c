/*
** EPITECH PROJECT, 2022
** Epitech-Template
** File description:
** main.c
*/

#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>

int bytes_available(int fd)
{
    int bytes_available = 0;

    if (ioctl(fd, FIONREAD, &bytes_available) == -1)
        return (-1);
    return (bytes_available);
}

void append_str_array(char ***array, char *what)
{
    int len = 0;

    if (*array)
        for (; (*array)[len]; len++);
    *array = realloc(*array, sizeof(char *) * (len + 2));
    (*array)[len] = what;
    (*array)[len + 1] = NULL;
}

void free_str_array(char **array)
{
    if (!array)
        return;
    for (int i = 0; array[i]; i++)
        free(array[i]);
    free(array);
}

void *memdup(void *src, size_t size)
{
    void *dst = calloc(1, size);

    memcpy(dst, src, size);
    return (dst);
}
