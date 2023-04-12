/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** test_compare
*/

#include <criterion/criterion.h>
#include "libmyteams.h"
#include "myteams.h"

Test(int_compare, int_compare, .init = setup, .fini = teardown)
{
    int a = 1;
    int b = 2;
    int c = 1;

    cr_assert_eq(int_compare((void *)(long)a, (void *)(long)b), -1);
    cr_assert_eq(int_compare((void *)(long)b, (void *)(long)a), 1);
    cr_assert_eq(int_compare((void *)(long)a, (void *)(long)c), 0);
}

Test(generate_uuid, generate_uuid, .init = setup, .fini = teardown)
{
    char uuid[R_UUID_LENGTH];

    generate_uuid(uuid);
    cr_assert_eq(strlen(uuid), UUID_LENGTH);
    cr_assert_eq(memchr(uuid, 0, UUID_LENGTH), NULL);
    cr_assert_eq(uuid[UUID_LENGTH], 0);
}
