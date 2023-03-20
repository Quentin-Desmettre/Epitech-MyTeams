/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** map
*/

#include "map.h"

map_t *map_create(int (*compare)(const void *, const void *),
void (*free_value)(void *))
{
    map_t *map = malloc(sizeof(map_t));

    map->capacity = 10;
    map->size = 0;
    map->elems = malloc(sizeof(map_elem_t) * map->capacity);
    map->compare = compare;
    map->free_value = free_value;
    return (map);
}

void map_destroy(map_t *map)
{
    if (!map)
        return;
    if (map->free_value)
        for (int i = 0; i < map->size; i++)
            map->free_value(map->elems[i].value);
    free(map->elems);
    free(map);
}

void map_add(map_t *map, void *key, void *value)
{
    int left = 0;
    int right = map->size - 1;
    int middle;
    int cmp_res;

    if (map->size == map->capacity) {
        map->capacity *= 2;
        map->elems = realloc(map->elems, sizeof(map_elem_t) * map->capacity);
    }
    while (left <= right) {
        middle = (left + right) / 2;
        if ((cmp_res = map->compare(map->elems[middle].key, key)) == 0)
            return map->free_value(map->elems[middle].value),
                    (void)(map->elems[middle].value = value);
        *(cmp_res < 0 ? &left : &right) = middle + (cmp_res < 0 ? 1 : -1);
    }
    for (int i = map->size - 1; i >= left; i--)
        map->elems[i + 1] = map->elems[i];
    map->elems[left] = (map_elem_t){key, value};
    map->size++;
}

void *map_get(map_t *map, void *key)
{
    int left = 0;
    int right = map->size - 1;
    int middle;
    int cmp_res;

    while (left <= right) {
        middle = (left + right) / 2;
        cmp_res = map->compare(map->elems[middle].key, key);
        if (cmp_res == 0)
            return (map->elems[middle].value);
        *(cmp_res < 0 ? &left : &right) = middle + (cmp_res < 0 ? 1 : -1);
    }
    return (NULL);
}

void map_remove(map_t *map, void *key)
{
    int left = 0;
    int right = map->size - 1;
    int middle;
    int cmp_res;

    while (left <= right) {
        middle = (left + right) / 2;
        cmp_res = map->compare(map->elems[middle].key, key);
        if (cmp_res != 0) {
            *(cmp_res < 0 ? &left : &right) = middle + (cmp_res < 0 ? 1 : -1);
            continue;
        }
        map->free_value ? map->free_value(map->elems[middle].value) : (void)0;
        for (int i = middle; i < map->size - 1; i++)
            map->elems[i] = map->elems[i + 1];
        map->size--;
        return;
    }
}
