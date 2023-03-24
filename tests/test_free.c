/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** test_free
*/

#include <criterion/criterion.h>
#include "libmyteams.h"
#define NO_INCLUDE_TEAMS
#include "server.h"

Test(free_cases, free_case)
{
    int fd = open("test", O_CREAT | O_RDWR, 0666);
    client_t cli = (client_t){.fd = fd, .buffer = strdup("test")};

    free_client(memdup(&cli, sizeof(client_t)));
    cr_assert_eq(bytes_available(fd), -1);

    free_message_list(NULL);

    team_t *team = malloc(sizeof(team_t));
    team->users = NULL;
    team->channels = NULL;
    free_team(team);

    channel_t *channel = malloc(sizeof(channel_t));
    channel->threads = NULL;
    free_channel(channel);

    thread_t *thread = malloc(sizeof(thread_t));
    thread->replies = NULL;
    free_thread(thread);
}
