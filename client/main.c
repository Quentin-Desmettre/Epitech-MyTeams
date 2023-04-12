/*
** EPITECH PROJECT, 2022
** Epitech-Template
** File description:
** main.c
*/

#include "client.h"

int help(void)
{
    printf("USAGE: ./myteams_server port\n\n");
    printf("\tip\tis the server ip address on which the server socket"
        " listens\n");
    printf("\tport\tis the port number on which the server socket listens\n");
    return 0;
}

int main(int ac, char **av)
{
    if (ac == 2 && !strcmp(av[1], "-help"))
        return help();
    if (ac != 3) {
        printf("Invalid number of arguments.\n");
        return 84;
    }
    client_t *client = client_init(av[1], av[2]);
    if (client == NULL)
        return 84;
    client_run(client);
    return 0;
}
