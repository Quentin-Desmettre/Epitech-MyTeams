/*
** EPITECH PROJECT, 2022
** Epitech-Template
** File description:
** main.c
*/

#include <stdio.h>
#include "server.h"

int main(int ac, char **av)
{
    int port = get_port(ac, av);
    server_t *serv = (port >= 0 ? init_server(port) : NULL);
    int rval;

    if (serv == NULL)
        return (ac == 2 && !strcmp(av[1], "-help")) ? 0 : 84;
    rval = run_server(serv);
    destroy_server(serv);
    return (rval);
}
