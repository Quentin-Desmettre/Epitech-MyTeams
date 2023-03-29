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

char *clean_command(char *command)
{
    char *new_command = calloc(1, sizeof(char) * (strlen(command) + 1));
    int nb_char = 0;

    for (int i = 0; command[i]; i++) {
        if (command[i] == ' ' || command[i] == '\t' || command[i] == '\n' ||
            command[i] == '\r' || command[i] == '\v' || command[i] == '\f' ||
            command[i] == '"')
            continue;
        new_command[nb_char] = command[i];
        nb_char++;
    }
    new_command = realloc(new_command, sizeof(char) * (nb_char + 1));
    new_command[nb_char] = '\0';
    free(command);
    return new_command;
}

int main(int ac, char **av)
{
    if (ac == 2 && !strcmp(av[1], "-help"))
        return help();
    if (ac != 3) {
        fprintf(stderr, "Invalid number of arguments.\n");
        return 84;
    }
    client_t *client = client_init(av[1], av[2]);
    if (client == NULL)
        return 84;
    client_run(client);
    return 0;
}
