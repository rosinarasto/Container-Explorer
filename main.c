#include <assert.h>
#include <inttypes.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "arguments.h"
#include "files.h"
#include "filter_print.h"
#include "data_source.h" // TODO: Read the content of this file.
#include "general.h"
#include "path.h"
#include "stations_neighbors.h"


void free_all(struct struct_array *lists, bool exists_neighbors) 
{
    for (size_t i = 0; i < lists->containers_length; i++) { 
        free(lists->containers[i].name);
        free(lists->containers[i].street);
        if (exists_neighbors) {
            free(lists->containers[i].neighbor.ids);
            free(lists->containers[i].neighbor.distance);
        }
    }

    for (size_t i = 0; i < lists->stations_length; i++) {
        free(lists->stations[i].container_ids);
        free(lists->stations[i].neighbors.ids);
        free(lists->stations[i].neighbors.distance);
    }

    free(lists->containers);
    free(lists->paths);
    free(lists->stations);

}

int main(int argc, char *argv[])
{
    struct switch_items switches = {
        .capacity_ceiling = 0, .capacity_floor = 0, .collection = 0,
        .g_source = 0, .g_target = 0, .publicity = ' ', .waste_types = 0, .type_chars = "APBGCT",
    };

    if (argc < 3 || !arguments_validation(argc, argv, &switches)) {
        fprintf(stderr, "Invalid input arguments\n");
        return EXIT_FAILURE;
    }

    struct struct_array lists = {
         .containers_length = 5, .paths_length = 5, .stations_length = 5,
         .containers = NULL, .paths = NULL, .stations = NULL,
         .possible_waste_types = { "Plastics and Aluminium", "Paper", "Biodegradable waste", "Clear glass", "Colored glass", "Textile" },
         .type_chars = "APBGCT",
    };

    lists.containers = calloc(lists.containers_length, sizeof(struct container_items));
    lists.paths = calloc(lists.paths_length, sizeof(struct path_items));
    lists.stations = calloc(lists.stations_length, sizeof(struct station_items));
    if (lists.containers == NULL || lists.paths == NULL || lists.stations == NULL) {
        fprintf(stderr, "Initialization fault\n");
        free_all(&lists, false);
        return EXIT_FAILURE;
    }

    if (!file_parse(argv, argc, &lists)) {
        fprintf(stderr, "Invalid input file\n");
        free_all(&lists, false);
        return EXIT_FAILURE;
    }

    if (!find_neighbors(&lists) || !find_stations(&lists)) {
        fprintf(stderr, "Initialization fault\n");
        free_all(&lists, true);
        return EXIT_FAILURE;
    }

    switch (switches.collection) {
    case S:
        print_stations(lists);
        break;
    case G:
        find_shortest_path(switches.g_source, switches.g_target, lists.stations, lists.stations_length);
        break;
    default:
        filter_and_print(lists, switches);;
    }
    free_all(&lists, true);

    return EXIT_SUCCESS; // May your program be as successful as this macro. Good luck!
}
