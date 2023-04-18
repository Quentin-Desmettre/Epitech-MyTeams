/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** fd_data
*/

#include <criterion/criterion.h>
#include "libmyteams.h"
#define NO_INCLUDE_TEAMS
#include "server.h"

Test(fd_data_init, fd_data_init)
{
    server_t serv;

    serv.fd = 3;
    serv.client_fds = memdup((int[3]){0, 1, 2}, sizeof(int) * 3);
    fd_data_init(&serv);
    cr_assert_eq(serv.fd, 3);
}

Test (remove_fd_from_array, remove_fd_from_array)
{
    int *array = memdup((int[3]){0, 1, 2}, sizeof(int) * 3);
    int len = 3;

    remove_fd_from_array(&array, &len, 2);
    cr_assert_eq(array[0], 0);
    cr_assert_eq(array[1], 1);
    cr_assert_eq(len, 2);

    remove_fd_from_array(&array, &len, 9);
    cr_assert_eq(array[0], 0);
    cr_assert_eq(array[1], 1);
    cr_assert_eq(len, 2);
}

Test(disconnect_client, disconnect_client)
{
    server_t serv;

}
