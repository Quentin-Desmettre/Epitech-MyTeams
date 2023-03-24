/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** test_linked_lists
*/

#include <criterion/criterion.h>
#include "libmyteams.h"
#include "myteams.h"

Test(append_node, append_node)
{
    list_t *list = NULL;

    append_node(&list, strdup("test"));
    cr_assert_str_eq(list->data, "test");
    cr_assert_eq(list->next, list);
    cr_assert_eq(list->prev, list);

    append_node(&list, strdup("test2"));
    cr_assert_str_eq(list->data, "test");
    cr_assert_str_eq(list->next->data, "test2");
    cr_assert_str_eq(list->prev->data, "test2");
    cr_assert_eq(list->next->next, list);
    cr_assert_eq(list->prev->prev, list);
    cr_assert_eq(list->next->prev, list);
    cr_assert_eq(list->prev->next, list);

    free_list(&list, free);
}

Test(push_to_front, push_to_front)
{
    list_t *list = NULL;

    append_node(&list, strdup("test"));
    cr_assert_str_eq(list->data, "test");
    cr_assert_eq(list->next, list);
    cr_assert_eq(list->prev, list);

    push_to_front(&list, strdup("test2"));
    cr_assert_str_eq(list->data, "test2");
    cr_assert_str_eq(list->next->data, "test");
    cr_assert_str_eq(list->prev->data, "test");
    cr_assert_eq(list->next->next, list);
    cr_assert_eq(list->prev->prev, list);
    cr_assert_eq(list->next->prev, list);
    cr_assert_eq(list->prev->next, list);

    free_list(&list, free);
}

Test(list_size, list_size)
{
    list_t *list = NULL;

    cr_assert_eq(list_size(list), 0);
    append_node(&list, strdup("test"));
    cr_assert_eq(list_size(list), 1);
    append_node(&list, strdup("test2"));
    cr_assert_eq(list_size(list), 2);
    append_node(&list, strdup("test3"));
    cr_assert_eq(list_size(list), 3);
    append_node(&list, strdup("test4"));
    cr_assert_eq(list_size(list), 4);
    append_node(&list, strdup("test5"));
    cr_assert_eq(list_size(list), 5);
    append_node(&list, strdup("test6"));
    cr_assert_eq(list_size(list), 6);
}

Test(remove_node, remove_node)
{
    list_t *list = NULL;

    remove_node(&list, 12, NULL);
    append_node(&list, strdup("test"));
    append_node(&list, strdup("test2"));
    remove_node(&list, 1, free);
    cr_assert_str_eq(list->data, "test");
    cr_assert_eq(list->next, list);
    cr_assert_eq(list->prev, list);
}
