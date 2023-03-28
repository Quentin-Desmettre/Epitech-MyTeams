/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** compare
*/

#include <uuid/uuid.h>
#include "myteams.h"

int int_compare(const void *a, const void *b)
{
    return (int)(long long)a - (int)(long long)b;
}

void generate_uuid(char uuid[R_UUID_LENGTH])
{
    uuid_t uuid_bin;

    uuid_generate(uuid_bin);
    uuid_unparse(uuid_bin, uuid);
}
