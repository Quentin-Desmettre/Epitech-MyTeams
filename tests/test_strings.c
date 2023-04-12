/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** test_strings
*/

#include <criterion/criterion.h>
#include "libmyteams.h"
#include "myteams.h"

Test(bytes_available, bytes_available, .init = setup)
{
    int fd = open("test", O_CREAT | O_RDWR | O_TRUNC, 0644);

    cr_assert_eq(bytes_available(fd), 0);
    write(fd, "test", 4);
    close(fd);
    fd = open("test", O_RDONLY);
    cr_assert_eq(bytes_available(fd), 4);
    close(fd);
    cr_assert_eq(bytes_available(fd), -1);
}

Test(memdup, memdup, .init = setup)
{
    char *str = "test";
    char *dup = memdup(str, 5);

    cr_assert_str_eq(str, dup);
    free(dup);
}

Test(free_str_array, free_str_array, .init = setup)
{
    char **array = calloc(1, sizeof(char *) * 3);

    array[0] = strdup("test");
    array[1] = strdup("test2");
    array[2] = NULL;
    free_str_array(array);
}

Test(append_str_array, append_str_array, .init = setup)
{
    char **array = NULL;

    append_str_array(&array, strdup("test"));
    cr_assert_str_eq(array[0], "test");
    cr_assert_eq(array[1], NULL);
    append_str_array(&array, strdup("test2"));
    cr_assert_str_eq(array[0], "test");
    cr_assert_str_eq(array[1], "test2");
    cr_assert_eq(array[2], NULL);
    free_str_array(array);
}
