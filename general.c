#include "general.h"

#include <assert.h>
#include <ctype.h>
#include <inttypes.h>
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool string_to_uint(const char *string, uintmax_t *uint_number, char wanted)
{
    assert(string != NULL);
    assert(uint_number != NULL);
    char *end;
    *uint_number = strtoumax(string, &end, 10);

    return (*uint_number < UINT_MAX && isdigit(string[0]) && (*end == wanted));
}

bool string_to_double(const char *string, double *double_num)
{
    assert(string != NULL);
    assert(double_num != NULL);
    char *end;
    *double_num = strtod(string, &end);
    const char *dot = strchr(string, '.');

    return (dot == NULL || (end - dot) <= 16) && (*end == '\0');
}

bool copy_string(char **new_string, const char *old_string)
{
    assert(new_string != NULL);
    assert(old_string != NULL);
    *new_string = malloc((strlen(old_string) + 1) * sizeof(char));
    if (*new_string == NULL) {
        return false;
    }

    strcpy(*new_string, old_string);

    return true;
}

struct neighbor_items *get_neighbor_items(uintmax_t id, struct container_items containers[], size_t container_length)
{
    assert(containers != NULL);

    for (size_t i = 0; i < container_length; i++) {
        if (containers[i].id == id) {
            return &(containers[i].neighbor);
        }

    }

    return NULL;
}

uintmax_t get_station_id(struct station_items stations[], size_t length, uintmax_t value)
{
    assert(stations != NULL);

    for (size_t i = 0; i < length; i++) {
        for (size_t j = 0; j < stations[i].current_index; j++) {
            if (stations[i].container_ids[j] == value) {
                return (i + 1);
            }

        }
    }

    assert(false);
}

void insert_sort(size_t length, struct neighbor_items *neighbor)
{
    assert(neighbor != NULL);
    size_t j;
    uintmax_t temp;

    for (size_t i = 1; i < length; i++) {
        j = i;
    
        while (j > 0 && (neighbor->ids[j] < neighbor->ids[j - 1])) {
            temp = neighbor->ids[j];
            neighbor->ids[j] = neighbor->ids[j - 1];
            neighbor->ids[j - 1] = temp;
            temp = neighbor->distance[j];
            neighbor->distance[j] = neighbor->distance[j - 1];
            neighbor->distance[j - 1] = temp;
            j--;
        }

    } 
}

bool realloc_array(void **pointer, size_t size)
{
    void *temp = (void *) realloc(*pointer, size);
    if (temp == NULL) {
        return false;
    }

    *pointer = temp;
 
    return true;
}
