/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** map
*/

#ifndef EPITECH_MYTEAMS_MAP_H
    #define EPITECH_MYTEAMS_MAP_H
    #include <stdlib.h>
    #define MCAST (void *)(long long)

typedef struct map_elem {
    void *key;
    void *value;
} map_elem_t;

typedef struct map {
    int capacity;
    int size;
    map_elem_t *elems;
    int (*compare)(const void *, const void *);
    void (*free_value)(void *);
} map_t;

typedef int (*compare_key_t)(const void *, const void *);
typedef void (*free_value_t)(void *);

map_t *map_create(compare_key_t compare, free_value_t free_value);
void map_destroy(map_t *map);

void map_add(map_t *map, void *key, void *value);
void *map_get(map_t *map, void *key);
void map_remove(map_t *map, void *key);


#endif //EPITECH_MYTEAMS_MAP_H
