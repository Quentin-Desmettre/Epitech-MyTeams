/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** compare
*/

#include <string.h>
#include <uuid/uuid.h>

int int_compare(const void *a, const void *b)
{
    return (int)a - (int)b;
}

void generate_uuid(char uuid[17])
{
    while (1) {
        uuid_generate((unsigned char*)uuid);
        if (memchr(uuid, 0, 16) == NULL)
            break;
    }
    uuid[16] = 0;
}
