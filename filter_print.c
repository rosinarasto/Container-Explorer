#include "filter_print.h"
#include "general.h"

#include <assert.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool filter_item(struct switch_items switches, struct container_items item)
{
    if ((switches.collection & T) == T && ((((uint16_t)1 << item.waste) & switches.waste_types) == 0)) {
        return false;
    }

    if ((switches.collection & C) == C && (item.capacity < switches.capacity_floor || item.capacity > switches.capacity_ceiling)) {
        return false;
    }

    if ((switches.collection & P) == P && (item.publicity != switches.publicity)) {
        return false;
    }

    return true;
}

void print_address(struct container_items item)
{
    if (item.street[0] != '\0') {
        printf(" %s", item.street);
    }
    if (item.is_address_number) {
        printf(" %ju", item.address_number);
    }

    printf(",");
}

void print_neighbors(size_t length, uintmax_t neighbors[])
{
    assert(neighbors != NULL);
    printf(" Neighbors:");

    for (size_t i = 0; i < length; i++) {
        if (i == 0 || neighbors[i] != neighbors[i - 1]){
            printf(" %ju", neighbors[i]);
        }
    }

    printf("\n");
}

void filter_and_print(struct struct_array lists, struct switch_items switches)
{
    for (size_t i = 0; i < lists.containers_length; i++) {
        if (filter_item(switches, lists.containers[i])) {
            printf("ID: %ju, Type: %s, Capacity: %ju, Address:", lists.containers[i].id, lists.possible_waste_types[lists.containers[i].waste], lists.containers[i].capacity);
            print_address(lists.containers[i]); //optional information
            print_neighbors(lists.containers[i].neighbor.length, lists.containers[i].neighbor.ids);
        }
    }
}

void print_waste_type(uint16_t waste_types, const char *type_chars)
{
    printf(";");

    for (size_t i = 0; i < 6; i++) {
        if ((waste_types & ((uint16_t) 1 << i)) != 0)
            printf("%c", type_chars[i]);
    }
}

void print_neighboring_stations(size_t length, uintmax_t neighbors[])
{
    assert(neighbors != NULL);
    printf(";");

    for (size_t i = 0; i < length; i++) {
        if (i == 0) {
            printf("%ju", neighbors[i]);
        } else if (neighbors[i] != neighbors[i - 1]) {
            printf(",%ju", neighbors[i]);
        }
    }

    printf("\n");
}

void print_stations(struct struct_array lists)
{   
    for (size_t i = 0; i < lists.stations_length; i++) {
        printf("%ld", (i + 1));
        print_waste_type(lists.stations[i].waste_types, lists.type_chars);
        print_neighboring_stations(lists.stations[i].neighbors.length, lists.stations[i].neighbors.ids);
    }

}
