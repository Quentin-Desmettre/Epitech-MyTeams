/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** header
*/

#include "server.h"
#include <sys/stat.h>

void write_header(char const *db)
{
    struct stat st = {0};
    int fd = open(db, O_WRONLY);
    int64_t size;

    if (stat(db, &st) == -1 || fd == -1)
        return (void)close(fd);
    size = st.st_size;
    write(fd, &size, sizeof(int64_t));
    close(fd);
}

bool check_header(int fd, char const *db)
{
    int64_t size;
    struct stat st = {0};

    if (stat(db, &st) == -1 || fd == -1)
        return false;
    read(fd, &size, sizeof(int64_t));
    if (size != st.st_size)
        return false;
    return true;
}
