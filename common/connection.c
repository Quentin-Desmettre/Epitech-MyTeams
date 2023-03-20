/*
** EPITECH PROJECT, 2022
** Epitech-Template
** File description:
** main.c
*/

#include "myteams.h"

user_t *create_user(int fd)
{
    user_t *user = calloc(sizeof(user_t), 1);

    user->fd = fd;
    return user;
}

void free_user(user_t *user)
{
    close(user->fd);
    free(user->buffer);
    free(user);
}
