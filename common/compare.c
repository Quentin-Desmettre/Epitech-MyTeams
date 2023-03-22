/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** compare
*/

#include <string.h>

int int_compare(const void *a, const void *b)
{
    return *(int *)a == *(int *)b;
}

int uuid_compare(const void *a, const void *b)
{
    return memcmp(a, b, 16);
}
