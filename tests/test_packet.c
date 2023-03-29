/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** test_packet
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "libmyteams.h"
#include "myteams.h"

Test(create_packet, create_packet, .init = setup, .fini = teardown)
{
    void *packet = create_packet(EV_LIST_MESSAGES, NULL, NULL, 0);

    cr_assert_eq(((uint64_t *)packet)[0], 11);
    cr_assert_eq(((uint8_t *)(packet + 8))[0], EV_LIST_MESSAGES);
    cr_assert_eq(((uint16_t *)(packet + 9))[0], 0);
    free(packet);
}

Test(create_packet, create_packet_args, .init = setup, .fini = teardown)
{
    char *arg = "test";
    char *arg2 = "test2";
    void *packet = create_packet(EV_LIST_MESSAGES, (const void *[]){arg, arg2},
            (const int[]){strlen(arg) + 1, strlen(arg2) + 1}, 2);

    cr_assert_eq(((uint64_t *)packet)[0], 11 + 2 + strlen(arg) + 1 + 2 +
            strlen(arg2) + 1);
    cr_assert_eq(((uint8_t *)(packet + 8))[0], EV_LIST_MESSAGES);
    cr_assert_eq(((uint16_t *)(packet + 9))[0], 2);
    cr_assert_eq(((uint16_t *)(packet + 11))[0], 5);
    cr_assert_str_eq(packet + 13, arg);
    cr_assert_eq(((uint16_t *)(packet + 13 + strlen(arg) + 1))[0], 6);
    cr_assert_str_eq(packet + 13 + strlen(arg) + 1 + 2, arg2);
    free(packet);
}


Test(append_arg_to_packet, append_arg_to_packet, .init = setup, .fini = teardown)
{
    void *packet = create_packet(EV_LIST_MESSAGES, NULL, NULL, 0);
    char *arg = "test";
    char *arg2 = "test2";

    cr_assert_eq(((uint64_t *)packet)[0], 11);
    cr_assert_eq(((uint8_t *)(packet + 8))[0], EV_LIST_MESSAGES);
    cr_assert_eq(((uint16_t *)(packet + 9))[0], 0);

    // Append 1 arg
    append_arg_to_packet(&packet, arg, strlen(arg) + 1);
    cr_assert_eq(((uint64_t *)packet)[0], 11 + 2 + strlen(arg) + 1);
    cr_assert_eq(((uint16_t *)(packet + 9))[0], 1);
    cr_assert_eq(((uint16_t *)(packet + 11))[0], 5);
    cr_assert_str_eq(packet + 13, "test");

    // Append 2nd arg
    append_arg_to_packet(&packet, arg2, 2);
    cr_assert_eq(((uint64_t *)packet)[0], 11 + 2 + strlen(arg) + 1 + 2 + 2);
    cr_assert_eq(((uint16_t *)(packet + 9))[0], 2);
    cr_assert_eq(((uint16_t *)(packet + 11))[0], 5);
    cr_assert_str_eq(packet + 13, "test");
    cr_assert_eq(((uint16_t *)(packet + 18))[0], 2);
    cr_assert_eq(*((char *)(packet + 20)), 't');
    cr_assert_eq(*((char *)(packet + 21)), 'e');
    free(packet);
}

Test(send_packet, send_packet, .init = setup, .fini = teardown)
{
    void *packet = malloc(sizeof(uint64_t) + 4);
    char dup_packet[sizeof(uint64_t) + 4];
    char content[sizeof(uint64_t) + 4];
    int fd = open("test", O_CREAT | O_RDWR, 0666);

    ((uint64_t *)packet)[0] = 12;
    memcpy(packet + 8, "test", 4);
    memcpy(dup_packet, packet, sizeof(uint64_t) + 4);
    send_packet(packet, fd, true);

    close(fd);
    fd = open("test", O_RDONLY);
    read(fd, content, sizeof(uint64_t) + 4);
    for (unsigned i = 0; i < sizeof(uint64_t) + 4; i++)
        cr_assert_eq(((char *) dup_packet)[i], content[i]);
}
