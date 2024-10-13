#include "stations_neighbors.h"
#include "general.h"

#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool add_neighbor(uintmax_t neighbor_id, uintmax_t distance, struct neighbor_items *neighbor)
{
    assert(neighbor != NULL);
    if (neighbor->current_index == (neighbor->length - 1)) {
        neighbor->length *= 2;
        if (!realloc_array((void **) &(neighbor->ids), neighbor->length * sizeof(uintmax_t)) || !realloc_array((void **) &(neighbor->distance), neighbor->length * sizeof(uintmax_t))) {
            return false;
        }
    }

    neighbor->ids[neighbor->current_index] = neighbor_id;
    neighbor->distance[neighbor->current_index] = distance;
    neighbor->current_index++;

    return true;
}

bool find_neighbors(struct struct_array *lists)
{
    assert(lists != NULL);

    for (size_t i = 0; i < lists->containers_length; i++) {
        lists->containers[i].neighbor.length = 5;
        lists->containers[i].neighbor.current_index = 0;
        lists->containers[i].neighbor.ids = calloc(lists->containers[i].neighbor.length, sizeof(uintmax_t));
        lists->containers[i].neighbor.distance = calloc(lists->containers[i].neighbor.length, sizeof(uintmax_t));

        for (size_t j = 0; j < lists->paths_length; j++) {
            if (lists->containers[i].id == lists->paths[j].id_a && !add_neighbor(lists->paths[j].id_b, lists->paths[j].distance, &(lists->containers[i].neighbor))) {
                return false;
            }
            if (lists->containers[i].id == lists->paths[j].id_b && !add_neighbor(lists->paths[j].id_a, lists->paths[j].distance, &(lists->containers[i].neighbor))) {
                return false;
            }

        }

        lists->containers[i].neighbor.length = lists->containers[i].neighbor.current_index;
        insert_sort(lists->containers[i].neighbor.length, &(lists->containers[i].neighbor));

    }

    return true;
}

void add_container_in_station(struct station_items stations[], size_t index, struct container_items container)
{
    stations[index].container_ids[stations[index].current_index] = container.id;
    stations[index].current_index++;
    stations[index].waste_types |= ((uint16_t)1 << container.waste);
}

bool station_inicialization(struct station_items stations[], size_t index, struct container_items container)
{
    assert(stations != NULL);
    stations[index].latitude = container.latitude;
    stations[index].longitude = container.longitude;
    stations[index].waste_types = 0;
    stations[index].current_index = 0;
    stations[index].length = 5;
    stations[index].container_ids = calloc(stations[index].length, sizeof(uintmax_t));

    return (stations[index].container_ids != NULL);
}

bool realloc_station(struct station_items *station)
{
    station->length *= 2;

    return realloc_array((void **) &(station->container_ids), station->length * sizeof(uintmax_t));
}

enum station_change add_station(struct container_items container, struct station_items stations[], size_t length)
{
    assert(stations != NULL);

    for (size_t i = 0; i < length; i++) {
        if (stations[i].current_index == (stations[i].length - 2) && !realloc_station(stations + i)) {
            return FAULT;
        }

        if (fabs(container.latitude - stations[i].latitude) < 1e-14 && fabs(container.longitude - stations[i].longitude) < 1e-14) {
            add_container_in_station(stations, i, container);
            return WITHOUT_CHANGE;
        }

    }

    if (!station_inicialization(stations, length, container)) {
        return FAULT;
    };

    add_container_in_station(stations, length, container);

    return NEW;
}

bool find_neighbouring_stations(struct struct_array *lists)
{
    assert(lists != NULL);

    for (size_t i = 0; i < lists->stations_length; i++) {
        lists->stations[i].neighbors.length = 5;
        lists->stations[i].neighbors.current_index = 0;
        lists->stations[i].neighbors.ids = calloc(lists->stations[i].neighbors.length, sizeof(uintmax_t));
        lists->stations[i].neighbors.distance = calloc(lists->stations[i].neighbors.length, sizeof(uintmax_t));

        for (size_t j = 0; j < lists->stations[i].current_index; j++) {
            struct neighbor_items *temp_items = get_neighbor_items(lists->stations[i].container_ids[j], lists->containers, lists->containers_length);
            if (temp_items == NULL) {
                return false;
            }

            for (size_t k = 0; k < temp_items->length; k++) {
                if (!add_neighbor(get_station_id(lists->stations, lists->stations_length, temp_items->ids[k]), temp_items->distance[k], &(lists->stations[i].neighbors))) {
                    return false;
                }

            }

        } 

        lists->stations[i].neighbors.length = lists->stations[i].neighbors.current_index;
        insert_sort(lists->stations[i].neighbors.length, &(lists->stations[i].neighbors));     
    }

    return true;
}

bool find_stations(struct struct_array *lists)
{
    assert(lists != NULL);
    size_t current_index = 0;
    enum station_change return_value;

    for (size_t i = 0; i < lists->containers_length; i++) {
        if (current_index == (lists->stations_length - 1)) {
            lists->stations_length *= 2;
            if (!realloc_array((void **) &(lists->stations), lists->stations_length * sizeof(struct station_items))) {
                return false;
            }
        }

        if ((return_value = add_station(lists->containers[i], lists->stations, current_index)) == FAULT) {
            return false;
        }

        if (return_value == NEW) {
            current_index++; // new station was initialized
        }
    }

    lists->stations_length = current_index;

    return find_neighbouring_stations(lists);
}
