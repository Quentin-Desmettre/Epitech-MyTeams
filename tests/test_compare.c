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

    cr_assert_eq(int_compare(&a, &b), -1);
    cr_assert_eq(int_compare(&b, &a), 1);
    cr_assert_eq(int_compare(&a, &c), 0);
}

Test(generate_uuid, generate_uuid, .init = setup, .fini = teardown)
{
    char uuid[17];

    generate_uuid(uuid);
    cr_assert_eq(strlen(uuid), 16);
    cr_assert_eq(memchr(uuid, 0, 16), NULL);
    cr_assert_eq(uuid[16], 0);
}
