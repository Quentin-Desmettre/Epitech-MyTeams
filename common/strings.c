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
    for (int i = 0; array[i]; i++)
        free(array[i]);
    free(array);
}

int int_compare(const void *a, const void *b)
{
    return *(int *)a == *(int *)b;
}

int uuid_compare(const void *a, const void *b)
{
    return memcmp(a, b, 16);
}
