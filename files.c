#include "files.h"
#include "general.h"
#include "data_source.h"

#include <assert.h>
#include <ctype.h>
#include <inttypes.h>
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool id_parse(struct struct_array *lists, size_t index)
{
    const char *id = get_container_id(index);
    assert(lists != NULL);
    assert(id != NULL);
    if (strlen(id) == 0 || !string_to_uint(id, &(lists->containers[index].id), '\0')) {
        return false;
    }

    for (uintmax_t i = 0; i < index; i++) {
        if (lists->containers[index].id == lists->containers[i].id) {
            return false;
        }

    }

    return true;
}

bool conatiner_x_y_parse(struct struct_array *lists, size_t index)
{
    assert(lists != NULL);
    const char *latitude = get_container_x(index);
    const char *longtitude = get_container_y(index);
    if (latitude == NULL || longtitude == NULL || strlen(latitude) == 0 || strlen(longtitude) == 0) {
        return false;
    }

    return (string_to_double(latitude, &(lists->containers[index].latitude)) && string_to_double(longtitude, &(lists->containers[index].longitude)));
}

bool waste_type_parse(struct struct_array *lists, size_t index)
{
    const char *waste_type = get_container_waste_type(index);
    assert(lists != NULL);
    assert(waste_type != NULL);

    for (size_t waste = 0; waste < 6; waste++) {
        if (strcmp(waste_type, lists->possible_waste_types[waste]) == 0) {
            lists->containers[index].waste = waste;
            return true;
        }

    }

    return false;
}

bool capacity_parse(struct struct_array *lists, size_t index)
{
    assert(lists != NULL);
    const char* capacity = get_container_capacity(index);

    return (capacity != NULL && strlen(capacity) != 0 && string_to_uint(capacity, &(lists->containers[index].capacity), '\0')); 
}

bool address_parse(struct struct_array *lists, size_t index)
{
    const char *name = get_container_name(index);
    const char *street = get_container_street(index);
    const char *number = get_container_number(index);

    if (name == NULL || street == NULL || number == NULL) {
        return false;
    } 

    if (!copy_string(&(lists->containers[index].name), name) || !copy_string(&(lists->containers[index].street), street)) {
        return false;
    }

    if (strlen(number) != 0) {
        lists->containers[index].is_address_number = true;
    }

    return (strlen(number) == 0 || string_to_uint(number, &(lists->containers[index].address_number), '\0'));

}

bool publicity_parse(struct struct_array *lists, size_t index)
{
    assert(lists != NULL);
    const char *publicity = get_container_public(index);
    if (publicity == NULL || (strcmp(publicity, "N") != 0 && strcmp(publicity, "Y") != 0)) {
        return false;
    }

    lists->containers[index].publicity = publicity[0];
    
    return true;
}

bool container_file_parse(struct struct_array *lists)
{
    assert(lists != NULL);
    size_t i;

    for (i = 0; get_container_id(i) != NULL; i++) {
        if (i == (lists->containers_length - 1)) {
            lists->containers_length *= 2;
            if (!realloc_array((void **) &(lists->containers), lists->containers_length * sizeof(struct container_items))) {
                return false;
            }
        }

        if (!waste_type_parse(lists, i) || !capacity_parse(lists, i) || !address_parse(lists, i) || !publicity_parse(lists, i) || !id_parse(lists, i) || !conatiner_x_y_parse(lists, i)) {
            return false;
        }

    }

    lists->containers_length = i;

    return true;
}

bool id_distance_parse(struct struct_array *lists, size_t index)
{
    assert(lists != NULL);
    const char *id_a = get_path_a_id(index);
    const char *id_b = get_path_b_id(index);
    const char *distance = get_path_distance(index);
    if (id_a == NULL || id_b == NULL || distance == NULL || strcmp(id_a, id_b) == 0) {
        return false;
    }

    if (!string_to_uint(id_a, &(lists->paths[index].id_a), '\0') || !string_to_uint(id_b, &(lists->paths[index].id_b), '\0') || !string_to_uint(distance, &(lists->paths[index].distance), '\0')) {
        return false;
    }

    uint8_t count = 0;

    for (size_t i = 0; i < lists->containers_length; i++) {
        if (lists->containers[i].id == lists->paths[index].id_a) {
            count++;
        }
        if (lists->containers[i].id == lists->paths[index].id_b) {
            count++;
        }

    }

    return (count == 2);
}

bool path_file_parse(struct struct_array *lists)
{
    assert(lists != NULL);
    size_t i;

    for (i = 0; get_path_a_id(i) != NULL; i++) {
        if (i == (lists->paths_length - 1)) {
            lists->paths_length *= 2;
            if (!realloc_array((void **) &(lists->paths), lists->paths_length * sizeof(struct path_items))) {
                return false;
            }
        }

        if (!id_distance_parse(lists, i)) {
            return false;
        }

    }

    lists->paths_length = i;

    return true;
}

bool file_parse(char *argv[], int argc, struct struct_array *lists)
{
    assert(lists != NULL);

    if (!init_data_source(argv[argc - 2], argv[argc - 1])) {
        return false;
    }

    if (!container_file_parse(lists) || !path_file_parse(lists)) {
        destroy_data_source();
        return false;
    }

    destroy_data_source();

    return true;
}

