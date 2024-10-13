#ifndef GENERAL_H
#define GENERAL_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>


enum waste_type
{
    PLASTICS_AND_ALUMINIUM = 0,
    PAPER = 1,
    BIODEGRADABLE_WASTE = 2,
    CLEAR_GLASS = 3,
    COLORED_GLASS = 4,
    TEXTILE = 5,
};

 enum switch_type 
{ 
    EMPTY = 0,
    T = 1,
    C = 2,
    P = 4,
    S = 8,
    G = 16
};

struct switch_items 
{
    uintmax_t capacity_ceiling;
    uintmax_t capacity_floor;
    uintmax_t g_source;
    uintmax_t g_target;
    char publicity;
    uint8_t collection;
    uint16_t waste_types;
    const char type_chars[8];
};

struct neighbor_items 
{
    uintmax_t *ids;
    uintmax_t *distance;
    size_t length;
    size_t current_index;
};

struct container_items 
{
    uintmax_t id;
    double latitude;
    double longitude;
    enum waste_type waste;
    uintmax_t capacity;
    char *name;
    char *street;
    uintmax_t address_number;
    bool is_address_number;
    char publicity;
    struct neighbor_items neighbor;
};

struct path_items 
{
    uintmax_t id_a;
    uintmax_t id_b;
    uintmax_t distance;
};

struct station_items 
{
    uintmax_t *container_ids;
    size_t length;
    size_t current_index;
    double latitude;
    double longitude;
    struct neighbor_items neighbors;
    uint16_t waste_types;
};

struct struct_array 
{
    size_t containers_length;
    size_t paths_length;
    size_t stations_length;
    struct container_items *containers;
    struct path_items *paths;
    struct station_items *stations;
    const char possible_waste_types[8][25];
    const char type_chars[8];
};

/**
 * @brief fucntion convert string to uint number and then checks if number is below UINT_MAX, is above 0 and has right format (*end == wanted)
 *
 * @param pointer to char that will be convert into uint
 *  
 * @param pointer to uint number, where will be converted string stored
 *  
 * @param character where should strtoumax function stop
 * 
 * @retval true if number is below UINT_MAX, is above 0 and has right format (strtoumax ended at wanted) 
 * 
 * @retval false if number is above UINT_MAX or is below 0 or doesnt have right format (strtoumax didnt end at wanted)
 */
bool string_to_uint(const char *string, uintmax_t *uint_number, char wanted);

/**
 * @brief function convert string into double in strtod function and checks if string is correct double number and has correct length 
 * 
 * @param pointer to char that will be converted into double
 *  
 * @param pointer to double number, where will be stored new value
 *  
 * @retval true if number has correct format (15 and less numbers behind ".") and strtod ended at '\0'
 * 
 * @retval false if number doesnt have correct format (16 or more numbers behind ".") or strtod didnt end at '\0'
 */
bool string_to_double(const char *string, double *double_num);

/**
 * @brief function copy old_string to new_string
 * 
 * @param pointer to pointer to char, where will be stored old value
 *  
 * @param pointer to char, where is stored old value
 *  
 * @retval true if allocation function ended successfully
 * 
 * @retval false if allocation function ended unsuccessfully
 */
bool copy_string(char **new_string, const char *old_string);

/**
 * @brief function iterate through all containers and if container_id is same as wanted_id, it returns pointer to container neighbors
 * 
 * @param wanted id
 * 
 * @param array of all containers
 *  
 * @param quantity of containers
 *  
 * @retval pointer to structure, which store inforamtion about neighbors, if particular id was found
 * 
 * @retval NULL if id is not in containers ids
 */
struct neighbor_items *get_neighbor_items(uintmax_t id, struct container_items containers[], size_t container_length);

/**
 * @brief in first loop function iterate through all stations,
 * in second loop functions iterate through containers of particular station and is looking for match with "value"
 * 
 * @param array of all stations
 *  
 * @param quantity of stations 
 * 
 * @param id of container, which is neighbor with container from different station
 * 
 * @retval id of station
 */
uintmax_t get_station_id(struct station_items stations[], size_t length, uintmax_t value);

/**
 * @brief function sorting neighbor ids and distances between them
 * 
 * @param quantity of neighbors
 *  
 * @param pointer to structure, which store information about neighbors
 */
void insert_sort(size_t length, struct neighbor_items *neighbor);

/**
 * @brief function realloc memory
 * 
 * @param pointer to pointer to void
 *  
 * @param data size, which should be alloc
 *  
 * @retval true if allocation was successful
 * 
 * @retval false if allocation was unsuccessful
 */
bool realloc_array(void **pointer, size_t size);

#endif // GENERAL_H